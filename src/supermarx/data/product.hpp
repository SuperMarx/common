#pragma once

#include <string>

#include <supermarx/reference.hpp>
#include <supermarx/measure.hpp>
#include <supermarx/datetime.hpp>

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct supermarket;
struct imagecitation;
struct productclass;

struct product
{
	std::string identifier; // Internal reference as used by scrapers

	reference<supermarket> supermarket_id;
	boost::optional<reference<imagecitation>> imagecitation_id;
	reference<productclass> productclass_id;

	std::string name;
	uint64_t volume;
	measure volume_measure;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::product,
		(std::string, identifier)
		(supermarx::reference<supermarx::data::supermarket>, supermarket_id)
		(boost::optional<supermarx::reference<supermarx::data::imagecitation>>, imagecitation_id)
		(supermarx::reference<supermarx::data::productclass>, productclass_id)
		(std::string, name)
		(uint64_t, volume)
		(supermarx::measure, volume_measure)
)
