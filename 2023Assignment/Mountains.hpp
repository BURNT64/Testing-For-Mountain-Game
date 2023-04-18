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

/**
 * @brief Custom exception class for incorrect file format errors
 *
 * This class represents a custom exception that can be thrown when there is an error in the
 * file format of the data that is being read. It inherits from the standard C++ exception class
 * `std::runtime_error`.
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
 * This class represents a set of mountain names and ranges that can be read from a set of files,
 * and provides methods for selecting a random mountain and checking whether a given mountain
 * belongs to a given range.
 */
class Mountains
{

    std::vector<std::string> mountains; /**< Vector of all mountain names. */
    std::map<std::string, std::vector<std::string>> mountainRanges; /**< Map that associates each range name with a vector of mountain names in that range. */

public:
    /**
     * @brief Construct a new Mountains object from a vector of filenames
     *
     * @param filenames Vector of filenames containing mountain and range data
     *
     * This constructor takes a vector of filenames containing mountain and range data, reads the data
     * from each file, and stores the mountain names and ranges internally.
     *
     * Time complexity: O(N*M), where N is the number of files and M is the number of lines in each file.
     *
     * @throw IncorrectFileFormatException if the file format is incorrect.
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
     * @brief Gets the name of a random mountain from the collection.
     * 
     * @return A string containing the name of a random mountain.
     * 
     * @note This function has a time complexity of O(1).
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
     * @brief Checks if a given mountain belongs to a given range.
     *
     * @param mountain A string containing the name of the mountain to be checked.
     * @param range A string containing the name of the range to be checked.
     *
     * @return true if the mountain belongs to the range, false otherwise.
     *
     * @note This function has a time complexity of O(log n), where n is the average number of mountains per range.
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