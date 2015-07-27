#pragma once

#include <utility>
#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct product_log
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	std::vector<std::string> messages;
	datetime retrieved_on;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::product_log,
		(std::string, identifier)
		(std::string, name)
		(std::vector<std::string>, messages)
		(supermarx::datetime, retrieved_on)
)
