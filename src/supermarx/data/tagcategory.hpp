#pragma once

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct tagcategory
{
	std::string name;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::tagcategory,
		(std::string, name)
)
