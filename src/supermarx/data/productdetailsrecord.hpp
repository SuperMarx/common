#pragma once

#include <string>

#include <supermarx/reference.hpp>
#include <supermarx/datetime.hpp>
#include <supermarx/confidence.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct productdetails;

struct productdetailsrecord
{
	reference<productdetails> productdetails_id;

	datetime retrieved_on;
	confidence confidence;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::productdetailsrecord,
		(supermarx::reference<supermarx::data::productdetails>, productdetails_id)
		(supermarx::datetime, retrieved_on)
		(supermarx::confidence, confidence)
)
