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
#include <chrono>

using namespace std;

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
private:
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
        std::uniform_int_distribution<int> dis(0, static_cast<int>(mountains.size()) - 1);
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

/**
 * @brief A class for a quiz user interface.
 *
 * This class represents a user interface for a mountain quiz game. The class
 * keeps track of the user's responses, scores, and other game statistics, and
 * provides methods for starting and running the game, as well as printing
 * the final game results.
 */

class userInterface
{
private:
    string UserResponse; // keep track of the user's response
    string playerName; // keep track of the playersName
    int correctScore = 0; // keep track of the user's correct answers
    int incorrectScore = 0; // keep track of the users wrong answers
    int questions = 0; // keep track of the number of questions asked
    std::vector<std::pair<std::string, double>> correct_answers; // keep track of correct answers and their response times
    std::vector<std::pair<std::string, double>> incorrect_answers; // keep track of correct answers and their response times

public:

    /**
   * @brief Starts the quiz game and provides instructions to the user.
   *
   * This method displays a welcome message and provides instructions for
   * the user to play the game. The method prompts the user to start the
   * game by typing "yes", and exits the program if the user types "no".
   * 
   * @note This method has a time complexity of O(1).
   * This method doesn't depend on the input size and performs 
   * a fixed number of operations regardless of the input.
   */
   
    void startQuiz()
    {
        cout << "\n\n---------------------------------------------------------------\n";
        cout << "Guess the random mountain!!!! Created by Will Allwood 2022-2023\n";
        cout << "---------------------------------------------------------------\n\n";
        cout << "Welcome to the Mountain game!\n\n";
        cout << "You will be repeatedly presented with random mountain names and must guess which of four mountain ranges it is in\n\n";

        string UserResponse;
        while (true)
        {
            cout << "Are you ready to take the quiz?\n\n"
                "yes/no" << endl;
            cin >> UserResponse;
            if (UserResponse == "yes")
            {
                cout << endl;
                cout << "Wonderful let the game begin!!!" << endl;
                cout << "You will be given a series of random mountains based of 4 mountain ranges" << endl;
                cout << "These mountain ranges are: Alps(A), Carpathians(C), Icelandic Highlands(I), and Pyrenees(P)" << endl;
                cout << "To answer, simply enter the letter corresponding to the mountain range (can be lower or upper case)" << endl;
                cout << "Points are awarded for every correct question answered within 10 seconds" << endl;
                cout << "If you take more than 10 seconds to answer you recieve no points" << endl;
                cout << "your points will be tallied up based on how many questions you answered/got right" << endl;
                cout << "This program is designed to run until you wish to exit/quit the program" << endl;
                cout << "If you wish to exit the program at any time simply type exit/quit instead of an answer" << endl;
                cout << "Good luck!!!\n" << endl;
                break;
            }
            else if (UserResponse == "no")
            {
                cout << "Thats a shame... come back when you are ready to play" << endl;
                exit(0);
            }
            else
            {
                cout << "Invalid input! Please enter either 'yes' or 'no'." << endl;
            }
        }
    }

    /**
     * @brief Runs the quiz game and keeps track of user's responses and scores.
     *
     * This method runs the quiz game and prompts the user to guess the mountain
     * range of a randomly selected mountain. The user's response time is measured
     * and recorded, and the user's score is updated based on the correctness and
     * timeliness of their response. The game continues until the user types "exit"
     * or "quit".
     * @note This method has a time complexity of O(infinity) as it runs an infinite loop 
     * and doesn't depend on the input size, so it doesn't have a finite time complexity.
     */

    void mechanics()
    {
        std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
        Mountains mountains(filenames); // create a Mountains object
        std::string mountain; // mountain name
        std::string range; // mountain range
        std::atomic<bool> timed_out(false); // flag to indicate if the user has timed out

        while (true)
        {
            // get a random mountain name
            mountain = mountains.getRandomMountain();
            std::cout << "Which range is " << mountain << " in? (A, C, I, or P) ";

            // measure response time
            auto start = std::chrono::high_resolution_clock::now();

            // check if the user wants to exit
            if (range == "exit" || range == "quit")
                break;

            try {
                std::cin >> range;

                // convert input letter to full mountain range name
                if (range == "A" || range == "a")
                    range = "Alps";
                else if (range == "C" || range == "c")
                    range = "Carpathians";
                else if (range == "I" || range == "i")
                    range = "Icelandic Highlands";
                else if (range == "P" || range == "p")
                    range = "Pyrenees";
                else {
                    // throw an exception if the input is not valid
                    throw std::invalid_argument("Invalid input");
                }

                // calculate response time in seconds
                auto end = std::chrono::high_resolution_clock::now();
                double response_time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

                questions++;

                // check if the response time is within 10 seconds
                if (response_time > 10.0) {
                    std::cout << "\nSorry, you took too long to answer.\n";
                }
                else {
                    // check if the mountain belongs to the specified range
                    if (mountains.checkRange(mountain, range)) {
                        std::cout << "\nCorrect, " << mountain << " is in the " << range << " range.\n";
                        correctScore++;

                        // store correct answer and response time in the vector
                        correct_answers.push_back(std::make_pair(mountain, response_time));
                    }
                    else {
                        std::cout << "\nIncorrect, " << mountain << " is not in the " << range << " range.\n";
                        incorrectScore++;

                        // store incorrect answer and response time in the vector
                        incorrect_answers.push_back(std::make_pair(mountain, response_time));
                    }
                }
                std::cout << "Your score is " << correctScore << "/" << questions << ".\n";
            }
            catch (const std::invalid_argument&) {
                std::cout << "\nSorry, the mountain range you typed in does not exist in this context.\n";
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the input
            }
        }
    }

    /**
     * @brief Prints the final results of the quiz game.
     *
     * This method prints the final results of the quiz game, including the number
     * of questions asked, the number of correct and incorrect answers, and the
     * response times for each of the correct and incorrect answers.
     * @note This method has a time complexity of O(n) as it
     * iterates through the list of questions and answers once 
     * to calculate the score and print the results. 
     * The time complexity will depend on the number of questions and answers provided as input.
     */

    void printResults()
    {
        // print out the user's results
        std::cout << "\n\n\n";
        std::cout << "Results:\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Player Name: " << playerName << "\n";
        std::cout << "Total questions asked: " << questions << "\n";
        std::cout << "Total correct answers: " << correctScore << "\n";
        std::cout << "Total incorrect answers: " << incorrectScore << "\n";
        std::cout << "Percentage correct: " << (double)correctScore / questions * 100 << "%\n";
        std::cout << "Percentage incorrect: " << (double)incorrectScore / questions * 100 << "%\n";

        // combine correct and incorrect answers into one vector
        std::vector<std::pair<std::string, double>> all_answers(correct_answers);
        all_answers.insert(all_answers.end(), incorrect_answers.begin(), incorrect_answers.end());

        // sort all answers by response time
        std::sort(all_answers.begin(), all_answers.end(), [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b)
            {
                return a.second < b.second;
            });

        // print out all answers in ascending order of response time
        std::cout << "\nAll answers in ascending order of response time:\n";
        std::cout << "----------------------------------------\n";
        for (auto& answer : all_answers)
        {
            std::cout << answer.first << ": " << answer.second << " seconds";
            if (std::find(correct_answers.begin(), correct_answers.end(), answer) != correct_answers.end()) {
                std::cout << " (Correct)\n";
            }
            else {
                std::cout << " (Incorrect)\n";
            }
        }
        std::cout << "----------------------------------------\n";


        std::ifstream inputFile;
        inputFile.open("results.csv");
        if (inputFile.peek() == std::ifstream::traits_type::eof()) {
            // Write the header line if the file is empty
            std::ofstream outputFile;
            outputFile.open("results.csv", std::ios::app);
            outputFile << "Player Name, Correct Answers, Incorrect Answers, Response Time (s)\n";
            outputFile.close();
        }
        else {
            // Check if the header line has already been written
            std::string firstLine;
            std::getline(inputFile, firstLine);
            if (firstLine != "Player Name, Correct Answers, Incorrect Answers, Response Time (s)") {
                // Write the header line if it hasn't been written yet
                inputFile.close();
                std::ofstream outputFile;
                outputFile.open("results.csv", std::ios::app);
                outputFile.seekp(0, std::ios::beg);
                outputFile << "Player Name, Correct Answers, Incorrect Answers, Response Time (s)\n";
                outputFile.close();
            }
            inputFile.close();
        }

        // Write data to the file
        std::ofstream outputFile;
        outputFile.open("results.csv", std::ios::app);
        for (size_t i = 0; i < all_answers.size(); ++i) {
            outputFile << playerName << ", " << correctScore << ", " << incorrectScore << ", " << all_answers[i].second << "\n";
        }
        outputFile.close();

        std::cout << "Results written into CSV file" << std::endl;
        std::cout << "Thank you for playing!" << std::endl;
    }
};