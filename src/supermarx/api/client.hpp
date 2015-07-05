#pragma once

#include <supermarx/id_t.hpp>

#include <supermarx/util/downloader.hpp>
#include <supermarx/serialization/serializer.hpp>
#include <supermarx/serialization/deserializer.hpp>

#include <supermarx/message/add_product.hpp>
#include <supermarx/message/add_product_image_citation.hpp>
#include <supermarx/message/product_summary.hpp>
#include <supermarx/message/tag.hpp>
#include <supermarx/message/session.hpp>

namespace supermarx
{
namespace api
{

class client
{
public:
	typedef std::unique_ptr<serializer> serializer_ptr;
	typedef std::unique_ptr<deserializer> deserializer_ptr;

private:
	std::string basepath;
	downloader dl;
	serializer_ptr s;
	deserializer_ptr d;

	boost::optional<message::sessiontoken> stok;

	std::string handle_response(downloader::response const& r) const;

public:
	client(std::string const& agent);
	client(std::string const& basepath, std::string const& agent);

	client(client&) = delete;
	void operator=(client&) = delete;

	void promote(std::string const& username, std::string const& password);

	message::product_summary get_product(id_t supermarket_id, std::string const& product_identifier);
	void add_product(id_t supermarket_id, message::add_product const& ap);

	void bind_tag(reference<data::supermarket> supermarket_id, std::string const& product_identifier, message::tag const& tag);

	void add_product_image_citation(id_t supermarket_id, std::string const& product_identifier, std::string const& original_uri, std::string const& source_uri, const datetime &retrieved_on, raw &&image);
};

}
}
