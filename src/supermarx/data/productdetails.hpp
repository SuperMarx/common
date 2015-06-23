#pragma once

#include <string>

#include <supermarx/reference.hpp>
#include <supermarx/datetime.hpp>

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct product;

struct productdetails
{
	reference<product> product_id;

	uint64_t orig_price; // In (euro)cents
	uint64_t price; // In (euro)cents, with discount applied
	uint64_t discount_amount;

	datetime valid_on;
	boost::optional<datetime> valid_until;
	datetime retrieved_on;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::productdetails,
		(supermarx::reference<supermarx::data::product>, product_id)
		(uint64_t, orig_price)
		(uint64_t, price)
		(uint64_t, discount_amount)
		(supermarx::datetime, valid_on)
		(boost::optional<supermarx::datetime>, valid_until)
		(supermarx::datetime, retrieved_on)
)
