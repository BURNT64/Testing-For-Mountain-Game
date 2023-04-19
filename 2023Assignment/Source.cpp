#include "Mountains.hpp"

using namespace std;


int main()
{
    string playerName;
    bool validName = false;

    while (!validName) {
        cout << "Please enter your name (max 20 characters): ";
        cin >> playerName;

        // Check if the player's name is longer than 20 characters
        if (playerName.length() > 20) {
            cout << "\nSorry your name cannot be longer than 20 characters please try again.\n" << endl;
        }
        else {
            validName = true;
        }
    }

    userInterface UI;
    UI.startQuiz();
    UI.mechanics();
    UI.printResults();
    return 0;
}