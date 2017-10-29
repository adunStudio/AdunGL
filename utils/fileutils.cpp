//
// Created by adun on 2017. 10. 30..
//

#include "fileutils.h"

namespace  AdunGL
{
    namespace utils
    {
        std::string read_file(const char* filepath)
        {
            FILE* file = fopen(filepath, "rb");

            if(file == nullptr)
                assert(file);

            fseek(file, 0, SEEK_END);

            unsigned long length = ftell(file);

            char* data = new char[length + 1];

            memset(data, 0, length + 1);

            fseek(file, 0, SEEK_SET);

            fread(data, 1, length, file);

            fclose(file);

            std::string result(data);

            delete[] data;

            return result;
        }
    }
}


//Users/adun/Desktop/AdunGL/test.txt