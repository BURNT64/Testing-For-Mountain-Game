#include "Mountains.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <random>

using namespace std;

Mountains::Mountains(std::vector<std::string>& filenames)
{
    for (const std::string& filename : filenames)
    {
        std::ifstream file(filename);
        std::string line;

        // Extract the range name from the filename
        std::string rangeName = filename.substr(0, filename.find(".txt"));

        // Add an empty vector for the current range to the mountainRanges map
        mountainRanges[rangeName] = std::vector<std::string>();

        while (std::getline(file, line))
        {
            // Add the line string to the appropriate range-specific vector
            mountainRanges[rangeName].push_back(line);

            // Add the line string to the "mountains" vector
            mountains.push_back(line);
        }
        file.close();
    }
}

std::string Mountains::getRandomMountain()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, mountains.size() - 1);
    int randomIndex = dis(gen);
    return mountains[randomIndex];
}

bool Mountains::checkRange(std::string mountain, std::string range)
{
    // Look up the range associated with the given mountain in the mountainRanges map
    auto it = mountainRanges.find(range);
    if (it == mountainRanges.end())
        return false; // The given range does not exist

    // Check whether the given mountain is in the range
    return std::find(it->second.begin(), it->second.end(), mountain) != it->second.end();
}