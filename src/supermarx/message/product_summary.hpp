#pragma once

#include <utility>
#include <supermarx/id_t.hpp>

#include <supermarx/data/product.hpp>
#include <supermarx/data/productdetails.hpp>

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{
struct productclass;
}

namespace message
{

struct product_summary
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;

	reference<data::productclass> productclass_id;

	uint64_t volume;
	measure volume_measure;

	uint64_t orig_price; // In (euro)cents
	uint64_t price; // In (euro)cents, with discount applied
	uint64_t discount_amount;

	datetime valid_on;

	boost::optional<reference<data::imagecitation>> imagecitation_id;

	static product_summary merge(data::product const& p, data::productdetails const& pd)
	{
		return product_summary({
			p.identifier,
			p.name,
			p.productclass_id,
			p.volume,
			p.volume_measure,
			pd.orig_price,
			pd.price,
			pd.discount_amount,
			pd.valid_on,
			p.imagecitation_id
		});
	}
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
			supermarx::message::product_summary,
			(std::string, identifier)
			(std::string, name)
			(supermarx::reference<supermarx::data::productclass>, productclass_id)
			(uint64_t, volume)
			(supermarx::measure, volume_measure)
			(uint64_t, orig_price)
			(uint64_t, price)
			(uint64_t, discount_amount)
			(supermarx::datetime, valid_on)
			(boost::optional<supermarx::reference<supermarx::data::imagecitation>>, imagecitation_id)
)
