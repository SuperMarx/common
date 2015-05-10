#pragma once

#include <utility>
#include <supermarx/id_t.hpp>

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct product_summary
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	uint64_t volume;
	measure volume_measure;

	uint64_t orig_price; // In (euro)cents
	uint64_t price; // In (euro)cents, with discount applied
	uint64_t discount_amount;

	datetime valid_on;

	boost::optional<id_t> imagecitation_id;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
			supermarx::api::product_summary,
			(std::string, identifier)
			(std::string, name)
			(uint64_t, volume)
			(supermarx::measure, volume_measure)
			(uint64_t, orig_price)
			(uint64_t, price)
			(uint64_t, discount_amount)
			(supermarx::datetime, valid_on)
			(boost::optional<supermarx::id_t>, imagecitation_id)
)
