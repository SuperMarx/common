#pragma once

#include <string>

#include <supermarx/reference.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace supermarx
{
namespace data
{

struct productdetailsrecord;

struct productlog
{
	reference<productdetailsrecord> productdetailsrecord_id;

	std::string description;
};

}
}

BOOST_FUSION_ADAPT_STRUCT(
		supermarx::data::productlog,
		(supermarx::reference<supermarx::data::productdetailsrecord>, productdetailsrecord_id)
		(std::string, description)
)
