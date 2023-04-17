#pragma once
#include <iostream>
#include <string>
#include <vector>

class GameClass
{
	int correctScore = 0; // keep track of the user's correct answers
	int incorrectScore = 0; // keep track of the users wrong answers
	int questions = 0; // keep track of the number of questions asked
	std::string mountain; // mountain name
	std::string range; // mountain range
	std::vector<std::pair<std::string, double>> correct_answers; // keep track of correct answers and their response times
	std::vector<std::pair<std::string, double>> incorrect_answers; // keep track of correct answers and their response times
};

