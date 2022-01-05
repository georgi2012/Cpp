#pragma once
#include <stdexcept>

class FileCantLoad : public std::exception {
public:
    const char* what() const throw()
    {
        return "File can not be opened.";
    }
};
