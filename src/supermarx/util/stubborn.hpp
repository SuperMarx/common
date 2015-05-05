#pragma once

#include <functional>

namespace supermarx
{

class stubborn
{
public:
	template<typename T>
	static T attempt(std::function<T()> const& f, size_t attempts = 5)
	{
		for(size_t i = 0; i < attempts; ++i)
		{
			try
			{
				return f();
			} catch(std::exception const& e)
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
