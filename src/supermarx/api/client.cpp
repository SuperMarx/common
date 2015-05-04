#include <supermarx/api/client.hpp>

#include <supermarx/serialization/msgpack_serializer.hpp>
#include <supermarx/serialization/msgpack_deserializer.hpp>

#include <supermarx/serialization/serialize_fusion.hpp>

#include <supermarx/api/add_product.hpp>

namespace supermarx
{
namespace api
{

static const std::string formatstr = "?format=msgpack";

template<typename T>
std::string post(client::serializer_ptr const& s, downloader& dl, std::string const& uri, std::string const& name, const T& x)
{
	serialize<T>(s, name, x);

	std::string payload;
	s->dump([&](const char* data, size_t size) {
		payload.insert(0, data, size);
	});
	s->clear();

	return dl.post(uri, {{"payload", payload}});
}


client::client(std::string const& _agent)
	: client("https://api.supermarx.nl", _agent)
{}

client::client(std::string const& _basepath, std::string const& _agent)
	: basepath(_basepath)
	, dl(_agent)
	, s(new msgpack_serializer())
	, d(new msgpack_deserializer())
{}

void client::add_product(product const& p, id_t supermarket_id, datetime retrieved_on, confidence c, std::vector<std::string> const& problems)
{
	api::add_product request({p, retrieved_on, c, problems});
	std::string response = post(s, dl, basepath + "/add_product/" + boost::lexical_cast<std::string>(supermarket_id) + formatstr, "add_product", request);

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
	{}

	std::cerr << response << std::endl;
	throw std::runtime_error("Did not receive valid response");
}

}
}
