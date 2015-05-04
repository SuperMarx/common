#pragma once

#include <string>
#include <supermarx/datetime.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{

enum class measure
{
    UNITS,
    MILLILITERS,
    MILLIGRAMS,
    MILLIMETERS
};

struct product
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

enum class confidence
{
	LOW,
	NEUTRAL,
	HIGH,
	PERFECT
};

inline std::string to_string(measure m)
{
	switch(m)
	{
	case measure::UNITS:
		return "UNITS";
	case measure::MILLILITERS:
		return "MILLILITERS";
	case measure::MILLIGRAMS:
		return "MILLIGRAMS";
	case measure::MILLIMETERS:
		return "MILLIMETERS";
	}
}

inline std::string to_string(confidence conf)
{
	switch(conf)
	{
	case confidence::LOW:
		return "LOW";
	case confidence::NEUTRAL:
		return "NEUTRAL";
	case confidence::HIGH:
		return "HIGH";
	case confidence::PERFECT:
		return "PERFECT";
	}
}

inline measure to_measure(std::string const& str)
{
	if(str == "UNITS")
		return measure::UNITS;
	else if(str == "MILLILITERS")
		return measure::MILLILITERS;
	else if(str == "MILLIGRAMS")
		return measure::MILLIGRAMS;
	else if(str == "MILLIMETERS")
		return measure::MILLIMETERS;

	throw std::runtime_error("Could not parse measure");
}

inline confidence to_confidence(std::string const& str)
{
	if(str == "LOW")
		return confidence::LOW;
	else if(str == "NEUTRAL")
		return confidence::NEUTRAL;
	else if(str == "HIGH")
		return confidence::HIGH;
	else if(str == "PERFECT")
		return confidence::PERFECT;

	throw std::runtime_error("Could not parse confidence");
}

}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::product,
		(std::string, identifier)
		(std::string, name)
		(uint64_t, volume)
		(supermarx::measure, volume_measure)
		(uint64_t, orig_price)
		(uint64_t, price)
		(uint64_t, discount_amount)

		(supermarx::datetime, valid_on)
)
