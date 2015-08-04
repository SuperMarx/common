#pragma once

#include <supermarx/measure.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{

struct normalized_price
{
	uint64_t price;
	uint64_t volume;
	measure volume_measure;
};

}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::normalized_price,
		(uint64_t, price)
		(uint64_t, volume)
		(supermarx::measure, volume_measure)
)
