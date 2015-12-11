#pragma once

#include <supermarx/util/cached_downloader.hpp>
#include <supermarx/util/stubborn.hpp>

#include <iostream>
#include <functional>
#include <deque>

namespace supermarx
{

class download_manager
{
public:
	typedef std::function<void(downloader::response)> f_t;
	typedef std::function<void()> error_f_t;

	struct job_t
	{
		std::string uri;
		f_t f;

		job_t(job_t const&) = delete;
		job_t(job_t&&) = default;
	};

private:
	cached_downloader& dl;
	std::deque<job_t> queue;
	error_f_t error_f;

	static void nil() {}

public:
	download_manager(cached_downloader& _dl, error_f_t const& _error_f = nil)
		: dl(_dl)
		, queue()
		, error_f(_error_f)
	{}

	void schedule(std::string const& _uri, f_t&& _f)
	{
		job_t j = {_uri, std::move(_f)};
		queue.emplace_back(std::move(j));
	}

	void process_all()
	{
		while(!queue.empty())
		{
			job_t j = std::move(queue.front());
			queue.pop_front();

			try
			{
				j.f(stubborn::attempt<downloader::response, downloader::error>([&]() {
					return dl.fetch(j.uri);
				}));
			} catch(std::runtime_error e)
			{
				std::cerr << "Failed " << j.uri << std::endl
					<< '\t' << e.what() << std::endl;
				error_f();
				continue;
			}
		}
	}
};

}
