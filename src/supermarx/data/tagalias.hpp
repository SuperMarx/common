#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct tag;
struct tagcategory;

struct tagalias
{
	reference<tag> tag_id;
	boost::optional<reference<tagcategory>> tagcategory_id;

	std::string name;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::tagalias,
		(supermarx::reference<supermarx::data::tag>, tag_id)
		(boost::optional<supermarx::reference<supermarx::data::tagcategory>>, tagcategory_id)
		(std::string, name)
)
