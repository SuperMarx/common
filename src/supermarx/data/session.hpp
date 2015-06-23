#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct karluser;

struct session
{
	reference<karluser> karluser_id;
	token token;
	datetime creation;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::session,
		(supermarx::reference<supermarx::data::karluser>, karluser_id)
		(supermarx::token, token)
		(supermarx::datetime, creation)
)
