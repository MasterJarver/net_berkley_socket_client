#include <iostream>
#include <string>
#include <fstream>
#include "getfilesize.h"

long long getFileSize(const char* fileName)
{

    std::ifstream is(fileName, std::ifstream::binary);
    if(!is)
    {
        std::cout << "Error Open File" << std::endl;
        return -1;
    }
    else
    {
        is.seekg (0, is.end);
        const long long size = (long long)is.tellg();
        is.close();
        return size;
    }
}
