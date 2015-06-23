#pragma once

#include <supermarx/message/product_base.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct add_product
{
	product_base p;
	datetime retrieved_on;
	confidence c;
	std::vector<std::string> problems;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::add_product,
		(supermarx::message::product_base, p)
		(supermarx::datetime, retrieved_on)
		(supermarx::confidence, c)
		(std::vector<std::string>, problems)
)
