#pragma once

#include <supermarx/id_t.hpp>
#include <supermarx/product.hpp>

#include <supermarx/util/downloader.hpp>
#include <supermarx/serialization/serializer.hpp>
#include <supermarx/serialization/deserializer.hpp>

#include <supermarx/api/product_summary.hpp>
#include <supermarx/api/add_product_image_citation.hpp>

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

public:
	client(std::string const& agent);
	client(std::string const& basepath, std::string const& agent);

	client(client&) = delete;
	void operator=(client&) = delete;

	api::product_summary get_product(id_t supermarket_id, std::string const& product_identifier);
	void add_product(product const& p, id_t supermarket_id, datetime retrieved_on, confidence c, std::vector<std::string> const& problems);

	void add_product_image_citation(id_t supermarket_id, std::string const& product_identifier, std::string const& original_uri, std::string const& source_uri, const datetime &retrieved_on, raw &&image);
};

}
}
