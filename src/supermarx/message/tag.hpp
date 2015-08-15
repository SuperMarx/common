#pragma once

#include <string>
#include <boost/optional.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct tag
{
	std::string name;
	std::string category;

	bool operator<(tag const& rhs) const
	{
		return name < rhs.name || category < rhs.category;
	}
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::tag,
		(std::string, name)
		(std::string, category)
)
