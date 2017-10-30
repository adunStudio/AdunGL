//
// Created by adun on 2017. 10. 30..
//

#ifndef ADUNGL_FILEUTILS_H
#define ADUNGL_FILEUTILS_H

#include <string>
#include <fstream>
#include <cassert>

namespace AdunGL
{
    namespace utils
    {
        struct FileUtils
        {
            static std::string read_file(const char* filepath);
        };
    }
}
#endif //ADUNGL_FILEUTILS_H
