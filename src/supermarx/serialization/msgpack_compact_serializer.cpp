#include "msgpack_compact_serializer.hpp"

namespace ruuster
{
	msgpack_compact_serializer::msgpack_compact_serializer()
	: buffer()
	, pk(&buffer)
	{}

	msgpack_compact_serializer::~msgpack_compact_serializer()
	{}

	void msgpack_compact_serializer::write(const std::string& x)
	{
		pk.pack_raw(x.size());
		pk.pack_raw_body(x.data(), x.size());
	}

	void msgpack_compact_serializer::write_array(const std::string& /*name*/, const size_t n)
	{
		pk.pack_array(n);
	}

	void msgpack_compact_serializer::write_object(const std::string& /*name*/, const size_t n)
	{
		pk.pack_array(n);
	}
	
	void msgpack_compact_serializer::write(const std::string& /*key*/, const id_t& x)
	{
		pk.pack_raw(x.data.size());
		//const unsigned char* -> const char; do not touch the data
		pk.pack_raw_body(reinterpret_cast<const char*>(x.data.data()), x.data.size());
	}

	void msgpack_compact_serializer::write(const std::string& /*key*/, const uint64_t x)
	{
		pk.pack_uint64(x);
	}

	void msgpack_compact_serializer::write(const std::string& /*key*/, const std::string& x)
	{
		write(x);
	}

	void msgpack_compact_serializer::dump(std::function<void(const char*, size_t)> f)
	{
		f(buffer.data(), buffer.size());
	}

	void msgpack_compact_serializer::clear()
	{
		buffer.clear();
	}
}
