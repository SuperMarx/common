#pragma once

#include <string>
#include <supermarx/datetime.hpp>
#include <supermarx/measure.hpp>
#include <supermarx/confidence.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct product_base
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	uint64_t volume;
	measure volume_measure;

	uint64_t orig_price; // In (euro)cents
	uint64_t price; // In (euro)cents, with discount applied
	uint64_t discount_amount;

	datetime valid_on;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::product_base,
		(std::string, identifier)
		(std::string, name)
		(uint64_t, volume)
		(supermarx::measure, volume_measure)
		(uint64_t, orig_price)
		(uint64_t, price)
		(uint64_t, discount_amount)

		(supermarx::datetime, valid_on)
)
