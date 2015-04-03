#pragma once

#include <utility>
#include <supermarx/product.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{

struct product_summary
{
	typedef std::pair<date, uint64_t> pricepoint_t;

	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	std::vector<pricepoint_t> pricehistory;
};

}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::product_summary,
		(std::string, identifier)
		(std::string, name)
		(std::vector<supermarx::product_summary::pricepoint_t>, pricehistory)
)
