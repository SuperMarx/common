#pragma once

#include <supermarx/qualified.hpp>

#include <supermarx/data/tag.hpp>
#include <supermarx/message/product_summary.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct productclass_summary
{
	std::string name;

	std::vector<qualified<data::tag>> tags;
	std::vector<message::product_summary> products;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
			supermarx::message::productclass_summary,
			(std::string, name)
			(std::vector<supermarx::qualified<supermarx::data::tag>>, tags)
			(std::vector<supermarx::message::product_summary>, products)
)
