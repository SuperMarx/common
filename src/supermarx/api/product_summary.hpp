#pragma once

#include <utility>
#include <supermarx/product.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct product_summary
{
	typedef std::pair<datetime, uint64_t> pricepoint_t;

	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	std::vector<pricepoint_t> pricehistory;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::api::product_summary,
		(std::string, identifier)
		(std::string, name)
		(std::vector<supermarx::api::product_summary::pricepoint_t>, pricehistory)
)
