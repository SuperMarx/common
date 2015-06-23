#pragma once

#include <string>

#include <supermarx/token.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct karluser
{
	std::string name;
	token password_salt;
	token password_hashed;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::karluser,
		(std::string, name)
		(supermarx::token, password_salt)
		(supermarx::token, password_hashed)
)
