#pragma once

#include <string>
#include <supermarx/datetime.hpp>

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
	unsigned int orig_price; // In (euro)cents
	unsigned int price; // In (euro)cents, with discount applied
	condition discount_condition;

	date valid_on;
	datetime retrieved_on;
};

}
