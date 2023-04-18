#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

/**
 * @brief The IncorrectFileFormatException class is a derived class from std::runtime_error.
 * It represents an exception that is thrown when a file with an incorrect format is read.
 */
class IncorrectFileFormatException : public std::runtime_error {
public:
    /**
     * @brief Construct a new IncorrectFileFormatException object with a given message.
     *
     * @param message A string containing the message that describes the exception.
     */
    IncorrectFileFormatException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief The Mountains class represents a collection of mountains and their corresponding ranges.
 */
class Mountains
{
    /**
     * @brief Vector containing the names of all the mountains.
     */
    std::vector<std::string> mountains;

    /**
     * @brief Map containing the names of all the ranges and their corresponding mountains.
     */
    std::map<std::string, std::vector<std::string>> mountainRanges;

public:
    /**
     * @brief Constructs a new Mountains object by reading the data from the given filenames.
     *
     * @param filenames A reference to a vector containing the names of the files to be read.
     *
     * @throws IncorrectFileFormatException If any of the files have an incorrect format.
     *
     * @note This constructor has a time complexity of O(n), where n is the total number of mountains and ranges in all the files.
     */
    Mountains(std::vector<std::string>& filenames);

    /**
     * @brief Gets the name of a random mountain from the collection.
     *
     * @return A string containing the name of a random mountain.
     *
     * @note This function has a time complexity of O(1).
     */
    std::string getRandomMountain();

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
    bool checkRange(std::string mountain, std::string range);
};

