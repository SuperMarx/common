#pragma once

#include <supermarx/id_t.hpp>
#include <supermarx/product.hpp>

#include <supermarx/util/downloader.hpp>
#include <supermarx/serialization/serializer.hpp>
#include <supermarx/serialization/deserializer.hpp>

namespace supermarx
{

class api
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
	api(std::string const& agent);
	api(std::string const& basepath, std::string const& agent);

	api(api&) = delete;
	void operator=(api&) = delete;

	void add_product(product const& p, id_t supermarket_id);
};

}
