#pragma once

#include <tinyxml2.h>
#include <stack>
#include <ruuster-common/serialization/serializer.hpp>

namespace ruuster
{
	class xml_serializer : public serializer
	{
	public:
		xml_serializer();
		virtual ~xml_serializer();

		virtual void write_array(const std::string& name, const size_t n);
		virtual void write_object(const std::string& name, const size_t n);
		
		virtual void write(const std::string& key, const id_t& x);
		virtual void write(const std::string& key, const uint64_t x);
		virtual void write(const std::string& key, const std::string& x);

		virtual void dump(std::function<void(const char*, size_t)> f);
		virtual void clear();

	private:
		void add_node(tinyxml2::XMLNode* n);

		struct stack_e
		{
			tinyxml2::XMLNode *node;
			size_t n, i;

			stack_e(tinyxml2::XMLNode *node, size_t n); 
		};

		tinyxml2::XMLDocument doc;
		std::stack<stack_e> stack;
	};
}
