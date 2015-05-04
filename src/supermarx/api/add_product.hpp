#pragma once

#include <supermarx/product.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct add_product
{
	product p;
	datetime retrieved_on;
	confidence c;
	std::vector<std::string> problems;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::api::add_product,
		(supermarx::product, p)
		(supermarx::datetime, retrieved_on)
		(supermarx::confidence, c)
		(std::vector<std::string>, problems)
)
