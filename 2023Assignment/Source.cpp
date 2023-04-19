#include "Mountains.hpp"

using namespace std;

// main function - program entry point
int main() 
{
    userInterface UI; // creates a userInterface object named UI
    UI.startQuiz(); // calls the startQuiz function of the UI object
    UI.mechanics(); // calls the mechanics function of the UI object
    UI.printResults(); // calls the printResults function of the UI object
    return 0; // indicates successful termination of the program
}