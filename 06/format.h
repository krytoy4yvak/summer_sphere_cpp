#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <utility>


enum class status {
    STRING,
    OPEN_CLIP,
    VALUE
};

class Custom_Exception: public std::runtime_error
{
public:
    Custom_Exception(const char* message)
        : std::runtime_error(message)
    {
    }
};

void unzip(std::vector<std::string>& vec)
{
}

template<class T>
void unzip(std::vector<std::string>& vec, const T& arg)
{
    std::stringstream stream;
    stream << arg;
    vec.push_back(stream.str());
}

template<class T, class... Args>
void unzip(std::vector<std::string>& vec, const T& arg, const Args&... args)
{
    std::stringstream stream;
    stream << arg;
    vec.push_back(stream.str());
    unzip(vec, args...);
}

template<class... Args>
std::string format(const std::string& str, const Args&... args)
{
    std::vector<std::string> vec;
    std::stringstream stream;
    unzip(vec, args...);

    auto st = status::STRING;
    size_t index = 0;
    for(auto c : str) {

        switch(st){
        case status::STRING:
            if (c == '}') {
                throw Custom_Exception("Closing bracket before opening one");
            } else if (c != '{') {
                stream << c;
            } else {
                st = status::OPEN_CLIP;
                index = 0;
            }
            break;

        case status::OPEN_CLIP:
            if (!std::isdigit(c)) {
                throw Custom_Exception("Digit expected");
            } else {
                index = c - '0';
                st = status::VALUE;
            }
            break;

        case status::VALUE:
            if (std::isdigit(c)) {
                index = index * 10 + c - '0';
            } else if (c == '}') {
                if (index >= vec.size()) {
                    throw Custom_Exception("Too few arguments");
                }
                stream << vec[index];
                st = status::STRING;
            } else {
                throw Custom_Exception("Expected some digit");
            }
            break;
        default:
            throw Custom_Exception("Some Error!");
        }
    }
    if (st == status::OPEN_CLIP || st == status::VALUE) {
        throw Custom_Exception("Bad string");
    }
    return stream.str();
}