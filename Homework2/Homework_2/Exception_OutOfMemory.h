#pragma once
#include <stdexcept>

class OutOfMemory : public std::exception {
public:
    const char* what() const throw()
    {
        return "Program could not allocate enough memory to finish the operation.";
    }
};

