#pragma once

#include <utility>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct product_history
{
	typedef std::pair<datetime, uint64_t> pricepoint_t;

	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	std::vector<pricepoint_t> pricehistory;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::product_history,
		(std::string, identifier)
		(std::string, name)
		(std::vector<supermarx::message::product_history::pricepoint_t>, pricehistory)
)
