#include "Mountains.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <thread>
#include <map>
#include <iomanip>
#include <utility>

using namespace std;

std::vector<std::string> filenames = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
Mountains mountains(filenames); // create a Mountains object
int correctScore = 0; // keep track of the user's correct answers
int incorrectScore = 0; // keep track of the users wrong answers
int questions = 0; // keep track of the number of questions asked
std::string mountain; // mountain name
std::string range; // mountain range
std::vector<std::pair<std::string, double>> correct_answers; // keep track of correct answers and their response times
std::vector<std::pair<std::string, double>> incorrect_answers; // keep track of correct answers and their response times
std::atomic<bool> timed_out(false); // flag to indicate if the user has timed out

void createUser()
{
    cout << "---------------------------------------------------------------\n";
    cout << "Guess the random mountain!!!! Created by Will Allwood 2022-2023\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "Welcome to the Mountain game!\n\n";
    cout << "You will be repeatedly presented with random mountain names and must guess which of four mountain ranges it is in\n\n";

    string playerName;
    cout << "Please enter your name: ";
    cin >> playerName;

    string UserResponse;
    cout << "\nAre you ready to take the quiz " << playerName << "?\n\n"
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
    }
    else
    {
        cout << "Thats a shame... come back when you are ready to play" << endl;
        exit(0);
    }
}

void mechanics()
{
    while (true)
    {
        // get a random mountain name
        mountain = mountains.getRandomMountain();
        std::cout << "Which range is " << mountain << " in? (A, C, I, or P) ";

        // measure response time

        auto start = std::chrono::high_resolution_clock::now();
        std::cin >> range;
        auto end = std::chrono::high_resolution_clock::now();

        // convert input letter to full mountain range name
        if (range == "A" || range == "a")
            range = "Alps";
        else if (range == "C" || range == "c")
            range = "Carpathians";
        else if (range == "I" || range == "i")
            range = "Icelandic Highlands";
        else if (range == "P" || range == "p")
            range = "Pyrenees";

        // calculate response time in seconds
        double response_time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        // check if the user wants to exit
        if (range == "exit" || range == "quit")
            break;
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
}

void printResults(const std::string& playerName, int questions, int correctScore, int incorrectScore,
    const std::vector<std::pair<std::string, double>>& correct_answers,
    const std::vector<std::pair<std::string, double>>& incorrect_answers)
{
    // print out the user's results
    std::cout << "\n\n\n";
    std::cout << "Results:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Player ID: " << playerName << "\n";
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

int main()
{
    createUser();
    mechanics();
    printResults("Player 1", questions, correctScore, incorrectScore, correct_answers, incorrect_answers);
    return 0;
}