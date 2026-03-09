
#include "timer.h"
#include <cmath>
#include <cstddef>

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

/////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Timer timer("single measurement");
		assert(equal(calculate(1'000'000), 1'000'000));
	}

	{
		Timer timer("series of 10 measurements");
		for (int i = 0; i < 10; ++i)
		{
			timer.start();
			volatile double dummy = calculate(100'000);
			timer.stop();
		}
		assert(timer.average() > 0.0);
	}

	{
		Timer timer("manual average check");
		timer.start();
		calculate(500'000);
		timer.stop();
		timer.start();
		calculate(500'000);
		timer.stop();
		double avg = timer.average();
		assert(avg > 0.0);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////