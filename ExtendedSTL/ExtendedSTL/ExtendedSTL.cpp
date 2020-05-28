#pragma once
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector> 
#include <chrono>
#include <random>

namespace eStd
{  
	template <typename T>
	using Value_type = typename T::value_type;

	std::random_device rd;
	std::mt19937 g(rd());

	template <typename T>
	void Print(const T& container)
	{
		std::copy(container.begin(), container.end(), std::ostream_iterator <Value_type<T> >(std::cout, " "));
	}

	template <typename T>
	void RemoveDuplicateSorted(T& container)
	{
		container.erase(std::unique(container.begin(), container.end()), container.end());
	}

	template <typename T, typename Comp = std::less<> >
	void RemoveDuplicateUnsorted(T& container, Comp comp = Comp())
	{
		std::sort(container.begin(), container.end(), comp);
		RemoveDuplicateSorted(container);
	} 

	template <typename T>
	void Shuffle(T& container)
	{
		std::shuffle(container.begin(), container.end(), g);
	}
}

namespace eStd
{
	template <typename T>
	class eVector: public std::vector<T>
	{
	public:
		using std::vector<T>::vector;
		
		T& operator[] (size_t index)
		{
			return this->at(index);
		}

		const T& operator[] (size_t index) const
		{
			return this->at(index);
		}
	};
}

namespace eStd
{
	class Timer
	{
	private: 
		using clock_t = std::chrono::high_resolution_clock;
		using second_t = std::chrono::duration<double, std::ratio<1> >;

		std::chrono::time_point<clock_t> m_beg;

	public:
		Timer() : m_beg(clock_t::now()) {}

		void Reset()
		{
			m_beg = clock_t::now();
		}

		double Elapsed() const
		{
			return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
		}
	};
}