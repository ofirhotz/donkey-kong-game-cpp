#include <windows.h>
#include <iostream>
//#include <conio.h> // For kbhit() and getch()
#include "TheDonkykongGame.h"
#include "io_utils.h"
#include "vector"

using namespace std;

// Function prototypes
void displayMenu();
void displayInstructions();
void exitGame();
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main(int argc, char* argv[]) {
    hideCursor();

    vector<string> args(argv, argv + argc);
    bool loadPassed = false, savePassed = false, silentPassed = false;
    string stepsFile, resultsFile;


    // Parse command-line arguments
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-load" ){//&& i +1  < args.size()) {
            loadPassed = true;
            stepsFile = "gameSteps.txt";
            resultsFile = stepsFile.substr(0, stepsFile.find_last_of('.')) + ".result.txt";
        }
        else if (args[i] == "-save"){// && i+1 < args.size()) {
            
            savePassed = true;
            stepsFile = "gameSteps.txt";
            resultsFile = stepsFile.substr(0, stepsFile.find_last_of('.')) + ".result.txt";
        }
        else if (args[i] == "-silent") {
            silentPassed = true;
        }
    }
  /*  for (const auto& arg : args) {
        if (arg == "-load") {
            loadPassed = true;
        }
        else if (arg == "-save") {
            savePassed = true;
        }
        else if (arg == "-silent") {
            silentPassed = true;
        }
    }*/
   

    // Initialize game object
    TheDonkykongGame game;
    

    if (loadPassed) {
        // Load and replay mode
        game.init();
        game.loadSteps(stepsFile);
        if (silentPassed) {
            game.runSilent(resultsFile); // Verify results without rendering
        }
        else {
            game.runReplay(); // Replay with rendering
        }
    }
    else if (savePassed) {
        // Save mode
        game.init();
        game.runAndSave(stepsFile, resultsFile);
       
    }
    else {
        // Normal mode
       
        char userInput;
        while (true) {
            setCursorPosition(0, 0);
            displayMenu();
            cout << "Press a key to choose an option..." << endl;
            if (_kbhit()) {
                userInput = _getch();
                switch (userInput) {
                case '1':
                    system("cls");
                    game.init();
                    game.run();
                    break;
                case '8':
                    system("cls");
                    displayInstructions();
                    break;
                case '9':
                    system("cls");
                    exitGame();
                    return 0;
                default:
                    cout << "Invalid input! Please select a valid option." << endl;
                    system("pause");
                }
            }
        }
    }

    return 0;
}

// Function to display the menu
void displayMenu() {
    setCursorPosition(0, 0);
    cout << "================ MAIN MENU ================" << endl;
    cout << "1. Start Game" << endl;
    cout << "8. Instructions and Keys" << endl;
    cout << "9. Exit" << endl;
    cout << "===========================================" << endl;
}

// Function to simulate starting the game

// Function to display instructions and keys
void displayInstructions() {
    cout << "================ INSTRUCTIONS =============" << endl;
    cout << "Use the following keys to play the game:" << endl;
    cout << "Arrow keys: Move Mario" << endl;
    cout << "'d': Move right" << endl;
    cout << "'a': Move left" << endl;
    cout << "'s': Stand still" << endl;
    cout << "'w': Jump" << endl;
    cout << "'w': Climb ladders" << endl;
    cout << "'w': Going do the ladders" << endl;
    cout << "'ESC': Quit the game" << endl;
    cout << "===========================================" << endl;
    cout << "Press any key to return to the menu." << endl;
    _getch(); // Wait for user to press any key
    system("cls");

}

// Function to handle exiting the game
void exitGame() {
    system("cls");
    cout << "Exiting the game. Goodbye!" << endl;
}


