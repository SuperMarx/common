#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct tagcategory;

struct tag
{
	boost::optional<reference<tag>> parent_id;
	boost::optional<reference<tagcategory>> tagcategory_id;

	std::string name;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::tag,
		(boost::optional<supermarx::reference<supermarx::data::tag>>, parent_id)
		(boost::optional<supermarx::reference<supermarx::data::tagcategory>>, tagcategory_id)
		(std::string, name)
)
