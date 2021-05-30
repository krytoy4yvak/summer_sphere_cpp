#include "parser.h"

#include <sstream>


TokenParser::TokenParser()
    : StartCallback(nullptr)
    , FinishCallback(nullptr)
    , DigitTokenCallback(nullptr)
    , StringTokenCallback(nullptr)
{
}


bool TokenParser::IsNumber(const std::string& str) {
    for (char c: str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


uint64_t TokenParser::StringToDouble (const std::string& str) {
    std::stringstream stream(str);
    uint64_t result;
    stream >> result;
    return result;
}


void TokenParser::SetStartCallback(std::function<void()> func) {
    StartCallback = func;
}


void TokenParser::SetFinishCallback(std::function<void()> func) {
    FinishCallback = func;
}


void TokenParser::SetDigitTokenCallback(std::function<void(int)> func) {
    DigitTokenCallback = func;
}


void TokenParser::SetStringTokenCallback(std::function<void(const std::string&)> func) {
    StringTokenCallback = func;
}


void TokenParser::ParseString(const std::string& str) {
    std::stringstream sstream(str + "\0");
    ParseStream(sstream);
}


void TokenParser::ParseStream(std::istream& is) {
    if (StartCallback != nullptr) { 
        StartCallback();
    }

    std::string token;
    while (is >> token) {
        if (IsNumber(token) && DigitTokenCallback != nullptr) {
            DigitTokenCallback(StringToDouble(token));
        } else if (StringTokenCallback != nullptr) {
            StringTokenCallback(token);
        }
    }
    
    if (FinishCallback != nullptr) {
        FinishCallback();
    }
}