#pragma once

#include <utility>
#include <supermarx/product.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct product_log
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	std::vector<std::string> messages;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::api::product_log,
		(std::string, identifier)
		(std::string, name)
		(std::vector<std::string>, messages)
)
