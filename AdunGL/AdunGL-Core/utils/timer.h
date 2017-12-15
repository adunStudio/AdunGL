#pragma once

//
// Created by adun on 2017. 11. 19..
//

#include <chrono>

namespace AdunGL
{
	namespace utils
	{
		using namespace std::chrono;

		typedef high_resolution_clock clock;
		typedef duration<float>          fs;

		class Timer
		{
		private:
			clock::time_point m_start;

		public:
			Timer()
			{
				reset();
			}

			void reset()
			{
				m_start = clock::now();
			}

			float elapsed()
			{
				return duration_cast<fs>(clock::now() - m_start).count() * 1.0f;// * 1000.0f;
			}

		};
	}
}