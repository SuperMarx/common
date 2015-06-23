#pragma once

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct supermarket
{
	std::string name;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::supermarket,
		(std::string, name)
)
