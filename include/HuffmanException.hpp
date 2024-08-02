#pragma once
#include <exception>

class HuffmanException : public std::exception 
{
public:
    HuffmanException(std::string message) : msg(message)
    {
    }
    const char * what () const noexcept
    {
        return msg.c_str();
    }

private:
    std::string msg;
};

class HuffmanInputException : public HuffmanException
{
public:
    HuffmanInputException(std::string message) : HuffmanException(message)
    {
        
    }
};