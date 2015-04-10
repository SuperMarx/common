#pragma once

#include <supermarx/id_t.hpp>
#include <supermarx/product.hpp>

#include <supermarx/util/downloader.hpp>
#include <supermarx/serialization/serializer.hpp>
#include <supermarx/serialization/deserializer.hpp>

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

	void add_product(product const& p, id_t supermarket_id, datetime retrieved_on, confidence c);
};

}
}
