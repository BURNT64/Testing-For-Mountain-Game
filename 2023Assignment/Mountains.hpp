#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <random>

using namespace std;

/**
 * @brief Custom exception class for incorrect file format errors
 *
 */
class IncorrectFileFormatException : public std::runtime_error {
public:

    /**
     * @brief Construct a new Incorrect File Format Exception object
     *
     * @param message Error message to be displayed
     */
    IncorrectFileFormatException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief A class for working with a set of mountain names and ranges
 *
 */
class Mountains
{

    std::vector<std::string> mountains;
    std::map<std::string, std::vector<std::string>> mountainRanges;

public:

    /**
     * @brief Construct a new Mountains object from a vector of filenames
     *
     * @param filenames Vector of filenames containing mountain and range data
     */
    Mountains(std::vector<std::string>& filenames)
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
                // Check that the line string is not empty and does not contain any whitespace
                if (line.empty() || std::isspace(line.front()) || std::isspace(line.back())) {
                    throw IncorrectFileFormatException("Incorrect file format in " + filename);
                }
                // Add the line string to the appropriate range-specific vector
                mountainRanges[rangeName].push_back(line);
                // Add the line string to the "mountains" vector
                mountains.push_back(line);
            }
            file.close();
        }
    }

    /**
     * @brief Get a random mountain name from the list of all mountain names
     *
     * @return std::string A random mountain name
     */
    std::string getRandomMountain()
    {
        if (mountains.empty()) {
            return "";
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, mountains.size() - 1);
        int randomIndex = dis(gen);
        return mountains[randomIndex];
    }

    /**
     * @brief Check whether a given mountain belongs to a given range
     *
     * @param mountain The name of the mountain to check
     * @param range The name of the range to check
     * @return true if the mountain belongs to the range
     * @return false if the mountain does not belong to the range
     */
    bool checkRange(std::string mountain, std::string range)
    {
        // Look up the range associated with the given mountain in the mountainRanges map
        auto it = mountainRanges.find(range);
        if (it == mountainRanges.end())
            return false; // The given range does not exist

        // Check whether the given mountain is in the range
        return std::find(it->second.begin(), it->second.end(), mountain) != it->second.end();
    }
};