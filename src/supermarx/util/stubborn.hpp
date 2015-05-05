#pragma once

#include <functional>

namespace supermarx
{

class stubborn
{
public:
	template<typename T, typename E = std::runtime_error>
	static T attempt(std::function<T()> const& f, size_t attempts = 5)
	{
		for(size_t i = 0; i < attempts; ++i)
		{
			try
			{
				return f();
			}
			catch(E const& e)
			{
				if(i >= attempts - 1) // If is last
					throw e;
			}
		}
	}

private:
	stubborn() = delete;
};

}
