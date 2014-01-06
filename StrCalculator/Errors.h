#pragma once
#include <exception>
#include <string>

class SyntaxError : public std::exception {
public:
    SyntaxError(std::string s) : std::exception(s.c_str()) {}
};

class RuntimeError : public std::exception {
public:
    RuntimeError(std::string s) : std::exception(s.c_str()) {}
};