#pragma once

#include <string>

namespace supermarx
{

enum class confidence
{
	LOW,
	NEUTRAL,
	HIGH,
	PERFECT
};

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
