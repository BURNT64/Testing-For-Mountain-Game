#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

class IncorrectFileFormatException : public std::runtime_error {
public:
    IncorrectFileFormatException(const std::string& message)
        : std::runtime_error(message) {}
};

class Mountains
{
    std::vector<std::string> mountains;
    std::map<std::string, std::vector<std::string>> mountainRanges;

public:
    Mountains(std::vector<std::string>& filenames);
    std::string getRandomMountain();
    bool checkRange(std::string mountain, std::string range);
};

