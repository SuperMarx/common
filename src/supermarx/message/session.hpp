#pragma once

#include <supermarx/reference.hpp>
#include <supermarx/token.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{

namespace data
{
struct sessionticket;
}

namespace message
{

struct sessionticket
{
	reference<data::sessionticket> id;
	token nonce;
	token salt;
};

typedef token sessiontoken;

}
}

BOOST_FUSION_ADAPT_STRUCT(
			supermarx::message::sessionticket,
			(supermarx::reference<supermarx::data::sessionticket>, id)
			(supermarx::token, nonce)
			(supermarx::token, salt)
)
