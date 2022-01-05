#pragma once
#include <stdexcept>

class ExitProgram : public std::exception {
public:
    const char* what() const throw()
    {
        return "Exiting program.";
    }
};

