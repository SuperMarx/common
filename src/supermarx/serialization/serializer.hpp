#pragma once

#include <string>
#include <functional>

#include <supermarx/datetime.hpp>
#include <supermarx/raw.hpp>
#include <supermarx/token.hpp>

namespace supermarx
{

class serializer
{
protected:
	serializer() {}
	
public:
	virtual ~serializer() {}

	virtual void write_array(const std::string& name, const size_t n) = 0;
	virtual void write_object(const std::string& name, const size_t n) = 0;

	virtual void write(const std::string& key, const uint64_t x) = 0;
	virtual void write(const std::string& key, const std::string& x) = 0;
	virtual void write(const std::string& key, const raw& x) = 0;
	virtual void write(const std::string& key, const token& x) = 0;

	virtual void dump(std::function<void(const char*, size_t)> f) = 0;
	virtual void clear() = 0;

	void write(const std::string& key, const bool x);
	void write(const std::string& key, const time x);
	void write(const std::string& key, const date x);
	void write(const std::string& key, const datetime x);
};

}
