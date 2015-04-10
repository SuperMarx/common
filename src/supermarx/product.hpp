#pragma once

#include <string>
#include <supermarx/datetime.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{

enum class condition
{
	ALWAYS,
	AT_TWO,
	AT_THREE
};

struct product
{
	std::string identifier; // Internal reference as used by scrapers
	std::string name;
	uint64_t orig_price; // In (euro)cents
	uint64_t price; // In (euro)cents, with discount applied
	condition discount_condition;

	datetime valid_on;
};

enum class confidence
{
	LOW,
	NEUTRAL,
	HIGH,
	PERFECT
};

inline std::string to_string(condition cond)
{
	switch(cond)
	{
	case condition::ALWAYS:
		return "ALWAYS";
	case condition::AT_TWO:
		return "AT_TWO";
	case condition::AT_THREE:
		return "AT_THREE";
	}
}

inline condition to_condition(std::string const& str)
{
	if(str == "ALWAYS")
		return condition::ALWAYS;
	else if(str == "AT_TWO")
		return condition::AT_TWO;
	else if(str == "AT_THREE")
		return condition::AT_THREE;

	throw std::runtime_error("Could not parse condition");
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
		(uint64_t, orig_price)
		(uint64_t, price)
		(supermarx::condition, discount_condition)

		(supermarx::datetime, valid_on)
)
