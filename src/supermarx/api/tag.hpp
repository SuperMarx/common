#pragma once

#include <string>
#include <boost/optional.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct tag
{
	std::string name;
	boost::optional<std::string> category;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::api::tag,
		(std::string, name)
		(boost::optional<std::string>, category)
)
