#pragma once

#include <iostream>
#include <functional>


class TokenParser
{
public:
    TokenParser();
    void SetStartCallback(std::function<void()>);
    void SetFinishCallback(std::function<void()>);
    void SetDigitTokenCallback(std::function<void(int)>);
    void SetStringTokenCallback(std::function<void(const std::string&)>);

    void ParseStream(std::istream& is);
    void ParseString(const std::string& str);

private:
    std::function<void()> StartCallback;
    std::function<void()> FinishCallback;
    std::function<void(double)> DigitTokenCallback;
    std::function<void(const std::string&)> StringTokenCallback;

    bool IsNumber(const std::string& str);
    uint64_t StringToDouble(const std::string& str);
};