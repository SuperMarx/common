#pragma once

#include <string>

#include <supermarx/reference.hpp>
#include <supermarx/datetime.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct supermarket;

struct imagecitation
{
	reference<supermarket> supermarket_id;

	std::string original_uri;
	std::string source_uri;

	int original_width;
	int original_height;

	datetime retrieved_on;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::imagecitation,
		(supermarx::reference<supermarx::data::supermarket>, supermarket_id)
		(std::string, original_uri)
		(std::string, source_uri)
		(int, original_width)
		(int, original_height)
		(supermarx::datetime, retrieved_on)
)
