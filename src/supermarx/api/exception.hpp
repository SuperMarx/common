#pragma once

namespace supermarx
{
namespace api
{

enum exception : uint64_t
{
	unknown =				101,
	backend_down =			102,
	state_unexpected =		103,

	path_unknown =			201,
	format_unknown =		202,
	product_not_found =		203,

	payload_expected =		301,
	session_expected =		302,

	authentication_error =	401,
	session_invalid =		402
};

}
}
