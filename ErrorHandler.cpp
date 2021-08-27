#include "ErrorHandler.h"


FileException :: FileException(string m)
{
    message = m;
}

const char* FileException ::what() const throw()
{
    return message.c_str();
}