#pragma once

#include <msgpack.hpp>
#include <ruuster-common/serialization/serializer.hpp>

namespace ruuster
{
	class msgpack_compact_serializer : public serializer
	{
	public:
		msgpack_compact_serializer();
		virtual ~msgpack_compact_serializer();

		virtual void write_array(const std::string& name, const size_t n);
		virtual void write_object(const std::string& name, const size_t n);
		
		virtual void write(const std::string& key, const id_t& x);
		virtual void write(const std::string& key, const uint64_t x);
		virtual void write(const std::string& key, const std::string& x);

		virtual void dump(std::function<void(const char*, size_t)> f);
		virtual void clear();

	private:
		void write(const std::string& x);

		msgpack::sbuffer buffer;
		msgpack::packer<msgpack::sbuffer> pk;
	};
}
