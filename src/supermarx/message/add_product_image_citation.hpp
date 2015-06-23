#pragma once

#include <supermarx/raw.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct add_product_image_citation
{
	std::string original_uri;
	std::string source_uri;

	datetime retrieved_on;

	raw image;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::add_product_image_citation,
		(std::string, original_uri)
		(std::string, source_uri)
		(supermarx::datetime, retrieved_on)
		(supermarx::raw, image)
)
