#pragma once

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <sstream>
#include <string>

namespace supermarx
{

class base64
{
public:
	static std::string conv(const char* buf, const size_t len)
	{
		typedef boost::archive::iterators::base64_from_binary<
				boost::archive::iterators::transform_width<const char *, 6, 8>
		> base64_text;

		std::stringstream ss;

		std::copy(
			base64_text(buf),
			base64_text(buf + len),
			boost::archive::iterators::ostream_iterator<char>(ss)
		);

		return ss.str();
	}

private:
	base64() = delete;
};

}
