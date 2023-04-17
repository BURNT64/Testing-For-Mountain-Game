#include "Mountains.h"
#include <iostream>
#include <string>
#include <vector>

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

class IncorrectFileFormatException : public std::exception {
public:
    IncorrectFileFormatException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }
private:
    std::string message_;
};
