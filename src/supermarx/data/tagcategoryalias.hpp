#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct tagcategory;

struct tagcategoryalias
{
	reference<tagcategory> tagcategory_id;

	std::string name;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::tagcategoryalias,
		(supermarx::reference<supermarx::data::tagcategory>, tagcategory_id)
		(std::string, name)
)
