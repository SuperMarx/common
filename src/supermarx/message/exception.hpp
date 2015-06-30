#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace message
{

struct exception
{
	uint64_t code;
	std::string message;
	std::string help;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::message::exception,
		(uint64_t, code)
		(std::string, message)
		(std::string, help)
)
