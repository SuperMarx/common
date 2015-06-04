#pragma once

#include <array>
#include <sstream>
#include <string>
#include <vector>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

namespace supermarx
{

typedef std::array<uint8_t, 32> token;

inline static std::string to_string(token const& tok)
{
	typedef
		boost::archive::iterators::base64_from_binary<
			boost::archive::iterators::transform_width<const char *, 6, 8>
		> byte_to_b64;

	std::stringstream os;
	std::copy(
		byte_to_b64(tok.data()),
		byte_to_b64(tok.data() + tok.size()),
		boost::archive::iterators::ostream_iterator<char>(os)
	);

	return os.str();
}

inline static token to_token(std::string const& str)
{
	typedef boost::archive::iterators::transform_width<
			boost::archive::iterators::binary_from_base64<const char *>, 8, 6
		> b64_to_byte;

	auto start(b64_to_byte(str.c_str()));
	auto end(b64_to_byte(str.c_str() + str.size()));

	token tok;
	assert((str.size() * 6)/8 == tok.size());
	std::copy(start, end, tok.data());

	return tok;
}

}
