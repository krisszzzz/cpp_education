#pragma once
/////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

/////////////////////////////////////////////////////////////////////////////////

// section : Chrono Management

/////////////////////////////////////////////////////////////////////////////////

// content : Timing

/////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>

#include <print>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer(std::string const & scope)
		: m_scope(scope)
		, m_running(true)
		, m_start(clock_t::now())
	{}

//  -----------------------------------------------------------------------------

   ~Timer()
	{
		if (m_running)
		{
			stop();
		}
		if (!m_durations.empty())
		{
			double sum = 0.0;
			for (auto const & d : m_durations)
				sum += d.count();
			std::print("{} : average = {:.6f} s\n", m_scope, sum / m_durations.size());
		}
	}

//  -----------------------------------------------------------------------------

	void start()
	{
		if (m_running)
		{
			stop();
		}
		m_running = true;
		m_start = clock_t::now();
	}

	void stop()
	{
		if (m_running)
		{
			auto end = clock_t::now();
			m_durations.push_back(std::chrono::duration_cast<D>(end - m_start));
			m_running = false;
		}
	}

//  -----------------------------------------------------------------------------

	double average() const
	{
		if (m_durations.empty())
			return 0.0;
		double sum = 0.0;
		for (auto const & d : m_durations)
			sum += d.count();
		return sum / m_durations.size();
	}

//  -----------------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (clock_t::now() - m_start);
	}

private :

	using clock_t = std::chrono::steady_clock;

//  -----------------------------------------------------------------------------

	std::string m_scope;

	bool m_running;

	clock_t::time_point m_start;

	std::vector < D > m_durations;
};

/////////////////////////////////////////////////////////////////////////////////

