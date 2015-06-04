#pragma once

#include <utility>
#include <array>
#include <supermarx/id_t.hpp>
#include <supermarx/token.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace api
{

struct sessionticket
{
	id_t id;
	token nonce;
	token salt;
};

typedef token sessiontoken;

}
}

BOOST_FUSION_ADAPT_STRUCT(
			supermarx::api::sessionticket,
			(supermarx::id_t, id)
			(supermarx::token, nonce)
			(supermarx::token, salt)
)
