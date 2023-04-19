#include "Mountains.hpp"

using namespace std;

int main()
{
    string playerName;
    cout << "Please enter your name: ";
    cin >> playerName;

    userInterface UI;
    UI.startQuiz();
    UI.mechanics();
    UI.printResults();
    return 0;
}