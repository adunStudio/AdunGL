#pragma once

#include <vector>
#include <string>
using namespace std;
namespace AdunGL
{
	namespace utils
	{
		static std::vector<string> split_string(const string& str, const char delimiter)
		{
			size_t start = 0;
			size_t end = str.find_first_of(delimiter);

			std::vector<string> result;

			while (end <= string::npos)
			{
				result.emplace_back(str.substr(start, end - start));

				if (end == string::npos)
					break;

				start = end + 1;
				end = str.find_first_of(delimiter, start);
			}

			return result;
		}
	}
}