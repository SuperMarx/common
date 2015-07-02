#include <supermarx/api/client.hpp>

#include <supermarx/api/exception.hpp>
#include <supermarx/api/session_operations.hpp>

#include <supermarx/serialization/msgpack_serializer.hpp>
#include <supermarx/serialization/msgpack_deserializer.hpp>

#include <supermarx/serialization/serialize_fusion.hpp>
#include <supermarx/serialization/deserialize_fusion.hpp>

#include <supermarx/message/exception.hpp>
#include <supermarx/message/add_product.hpp>

namespace supermarx
{
namespace api
{

static const std::string formatstr = "?format=msgpack";

template<typename T>
downloader::response post(client::serializer_ptr const& s, downloader& dl, std::string const& uri, std::string const& name, const T& x, boost::optional<message::sessiontoken> const& stok)
{
	serialize<T>(s, name, x);

	std::string payload;
	s->dump([&](const char* data, size_t size) {
		payload.insert(0, data, size);
	});
	s->clear();

	if(!stok)
		return dl.post(uri, {{"payload", payload}});
	else
		return dl.post(uri, {{"payload", payload}, {"sessiontoken", to_string(*stok)}});
}


std::string client::handle_response(const downloader::response &r) const
{
	if(r.code == 200) // HTTP OK
		return r.body;

	d->feed(r.body);
	auto e(deserialize<message::exception>(d, "exception"));

	throw static_cast<api::exception>(e.code);
}

client::client(std::string const& _agent)
	: client("https://api.supermarx.nl", _agent)
{}

client::client(std::string const& _basepath, std::string const& _agent)
	: basepath(_basepath)
	, dl(_agent)
	, s(new msgpack_serializer())
	, d(new msgpack_deserializer())
	, stok()
{}

void client::promote(std::string const& username, std::string const& password)
{
	d->feed(handle_response(dl.fetch(basepath + "/create_sessionticket/" + username + formatstr)));

	auto st(deserialize<message::sessionticket>(d, "sessiontoken"));

	token const passphrase_salted(hash(password, st.salt));
	token const passphrase_hashed(hash(passphrase_salted, st.nonce));

	d->feed(handle_response(dl.post(basepath + "/login/" + boost::lexical_cast<std::string>(st.id.unseal()) + formatstr, {{"password_hashed", to_string(passphrase_hashed)}})));

	stok.reset(deserialize<message::sessiontoken>(d, "sessiontoken"));
}

message::product_summary client::get_product(id_t supermarket_id, const std::string &product_identifier)
{
	d->feed(handle_response(dl.fetch(basepath + "/get_product/" + boost::lexical_cast<std::string>(supermarket_id) + "/" + product_identifier + formatstr)));
	auto result(deserialize<message::product_summary>(d, "product_summary"));
	return result;
}

void client::add_product(id_t supermarket_id, message::add_product const& ap)
{
	std::string response = handle_response(post(s, dl, basepath + "/add_product/" + boost::lexical_cast<std::string>(supermarket_id) + formatstr, "add_product", ap, stok));

	try
	{
		d->feed(response);
		std::string result;
		d->read_object("response");
		d->read("status", result);

		if(result == "done")
			return;
	}
	catch( ... )
	{
		d.reset(new msgpack_deserializer()); // State uncertain; flush
	}

	std::cerr << response << std::endl;
	throw std::runtime_error("Did not receive valid response");
}

void client::add_product_image_citation(id_t supermarket_id, std::string const& product_identifier, std::string const& original_uri, std::string const& source_uri, const datetime &retrieved_on, raw &&image)
{
	message::add_product_image_citation request({
		original_uri,
		source_uri,
		retrieved_on,
		std::move(image)
	});

	std::string response = handle_response(post(s, dl, basepath + "/add_product_image_citation/" + boost::lexical_cast<std::string>(supermarket_id) + "/" + product_identifier + formatstr, "add_product_image_citation", request, stok));
	try
	{
		d->feed(response);
		std::string result;
		d->read_object("response");
		d->read("status", result);

		if(result == "done")
			return;
	}
	catch( ... )
	{
		d.reset(new msgpack_deserializer()); // State uncertain; flush
	}

	std::cerr << response << std::endl;
	throw std::runtime_error("Did not receive valid response");
}


}
}
