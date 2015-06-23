#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct karluser;

struct sessionticket
{
	reference<karluser> karluser_id;
	token nonce;
	datetime creation;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::sessionticket,
		(supermarx::reference<supermarx::data::karluser>, karluser_id)
		(supermarx::token, nonce)
		(supermarx::datetime, creation)
)
