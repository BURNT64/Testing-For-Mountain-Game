#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;

class Mountains
{
    std::vector<std::string> mountains;
    std::map<std::string, std::vector<std::string>> mountainRanges;

public:
    Mountains(std::vector<std::string>& filenames);
    std::string getRandomMountain();
    bool checkRange(std::string mountain, std::string range);
};