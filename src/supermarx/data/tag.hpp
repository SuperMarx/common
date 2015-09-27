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
	reference<tagcategory> tagcategory_id;

	std::string name;
	bool canonical;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::tag,
		(boost::optional<supermarx::reference<supermarx::data::tag>>, parent_id)
		(supermarx::reference<supermarx::data::tagcategory>, tagcategory_id)
		(std::string, name)
		(bool, canonical)
)
