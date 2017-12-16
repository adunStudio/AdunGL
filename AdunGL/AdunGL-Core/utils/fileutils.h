#pragma once

//
// Created by adun on 2017. 10. 30..
//



#include <string>
#include <fstream>
#include <cassert>
#include "log.h"

namespace AdunGL
{
	namespace utils
	{
		struct FileUtils
		{
			static std::string read_file(const std::string& filepath);
		};
	}
}