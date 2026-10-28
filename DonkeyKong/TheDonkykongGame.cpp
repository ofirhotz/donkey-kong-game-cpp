#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include "TheDonkykongGame.h"
#include "Mario.h"
#include"Barrels.h"
#include "Ghosts.h"
#include "Steps.h"
#include <sstream>
#include "SGhosts.h"


using namespace std;
vector<Ghost> ghosts;
vector<SGhosts> Sghosts;
vector<Barrel> barrels;
int barrelSpawnTimer = 0;
int monkeyX, monkeyY;



void printColoredChar(char c, const std::string& colorCode) {
    std::cout << colorCode << c << "\033[0m"; // Reset the color after printing the character
}


int getRandom(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
std::vector<std::tuple<int, std::string, std::string, int>> steps;
int livesLost = 0;
int finishTime = 0;
int score = 0;

std::vector<Step> TheDonkykongGame::getRelevantSteps(int currentTime) {
    std::vector<Step> steps;

    // Log Mario's movement
   /* static int prevMarioX = m[0].getX();
    static int prevMarioY = m[0].getY();
    if (m[0].getX() != prevMarioX || m[0].getY() != prevMarioY) {
        steps.push_back({ currentTime, "Mario", "MOVE" , m[0].direction});
        prevMarioX = m[0].getX();
        prevMarioY = m[0].getY();
    }*/

    steps.push_back({ currentTime, "Mario", "MOVE" , m[0].direction });
    // Log Mario's jump

    // Log Mario's attack

    if (m[0].hammer)
    {
        steps.push_back({ currentTime, "Mario" , "HAMMER" , m[0].direction });
    }
    if (m[0].attack) {
        steps.push_back({ currentTime, "Mario", "ATTACK" , m[0].direction});
    }

    // Log barrel spawns
   /* for (const auto& barrel : barrels) {
        steps.push_back({ currentTime, "Barrel", "SPAWN" });
    }

    // Log ghost movements
    for (const auto& ghost : ghosts) {
        steps.push_back({ currentTime, "Ghost", "MOVE" });
    }*/

    return steps;
}





void TheDonkykongGame::spawnBarrel(int monkeyX, int monkeyY) 
{
    barrels.push_back(Barrel(monkeyX, monkeyY + 1, 3));

}
void TheDonkykongGame::updateBarrels()
{
    for (size_t i = 0; i < barrels.size(); i++)
    {
        barrels[i].move();
       /* gotoxy(90, 1);
        printf("x:%d  y:%d\n", m[0].getX(), m[0].getY());
        gotoxy(85, 5);
        
        printf("barrel %d x:%d  y: %d\n",i, barrels[i].getX(), barrels[i].getY());*/

        if (barrels[i].metMario == true && m[0].attack == true)
        {
            barrels[i].explode();
   
       }
    
    }
   }


void TheDonkykongGame::removeSGhost(int ghostIndex) {
    // Remove the ghost at the given index from the ghosts vector
    Sghosts.erase(Sghosts.begin() + ghostIndex);
}
void TheDonkykongGame::removeGhost(int ghostIndex) {
    // Remove the ghost at the given index from the ghosts vector
    ghosts.erase(ghosts.begin() + ghostIndex);
}
void TheDonkykongGame::removeBarrel(int barrelIndex) {
    // Remove the barrel at the given index from the barrels vector
    barrels.erase(barrels.begin() + barrelIndex);
}


/*void TheDonkykongGame::spawnGhosts()
{
    int x = 18;
    static int y = 9;
    
    ghosts.push_back(Ghost(x, y, 3));

    y = y + 5;

}*/
void TheDonkykongGame::updateGhosts()
{
    for (size_t i = 0; i < ghosts.size(); i++)
    {
        ghosts[i].move();
        if (m[0].getX() == ghosts[i].getX() && m[0].getY() == ghosts[i].getY()) {
            // Handle the collision (e.g., remove the ghost, lose a life, etc.)
            // Lose a life if Mario hits a ghost
            removeGhost(i);   // Remove the ghost from the vector
            i--;              // Adjust index after removal
        }
       
    }
}

void TheDonkykongGame::updateSGhosts()
{
    for (size_t i = 0; i < Sghosts.size(); i++)
    {
        Sghosts[i].move();
        if (m[0].getX() == Sghosts[i].getX() && m[0].getY() == Sghosts[i].getY()) {
            // Handle the collision (e.g., remove the ghost, lose a life, etc.)
            // Lose a life if Mario hits a ghost
            removeSGhost(i);   // Remove the ghost from the vector
            i--;              // Adjust index after removal
        }

    }

}

/*bool TheDonkykongGame::checkCollision(const Ghost& ghost, const Barrel& barrel) {
    if (ghost.getX() == barrel.getX() && ghost.getY() == barrel.getY()) {
        // Example: Mark entities as having collided
        // ghost.setCollided(true);
        // barrel.setCollided(true);
        return true;
    }
    return false;
}


void TheDonkykongGame::updateGhostsAndBarrels() {
    for (size_t i = 0; i < ghosts.size(); i++) {
        for (size_t j = 0; j < barrels.size(); j++) {
            if (checkCollision(ghosts[i], barrels[j])) {
              
            }
        }
    }
}*/




vector<string> screens = { "level1.screen", "level2.screen", "level3.screen" }; // List of level files
size_t currentLevel = 0;

// Load level from a .screen file
char board[HEIGHT][WIDTH];  // 2D array to hold the board data

bool TheDonkykongGame::loadLevel(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    // Read level data from file
    
    //m[0].resetPosition();
    int coly =0;
    string line;
    int row = 0;
    while (getline(file, line) && row < HEIGHT ) {
        for (size_t col = 0; col < line.size() && col < WIDTH   ; col++) {
            board[row][col] = line[col];
           /* if (line[col] == 'P') { // Pauline's position
                paulineX = col;
                paulineY = row;
            }
            else if (line[col] == 'M') { // Mario's starting position
                marioX = col;
                marioY = row;
            }*/
            if (line[col] == 'X')
            {
                Sghosts.push_back(SGhosts(col, row, 3));

            }
            if (line[col] == 'x')
            {
                ghosts.push_back(Ghost(col, row, 3));
               
            }
            if (line[col] == '&')
            {
                monkeyX = col;
                monkeyY = row;

            }
            if (line[col] == '@')
            {
                coly = col;
                m[0].startingX = col;
                m[0].startingY = row;
              
                //mX = col;
                //mY = row;
               
               
                
            }
            if (line[col] == 'L')
            {
                m[0].livesX = col;
                m[0].livesY = row;
                
                
            }
        }
        row++;
    }
    //m[0] = Mario();
    // system("cls");
    //m[0].resetPosition(m[0].startingX, m[0].startingY);
    m[0].resetPosition(m[0].startingX , m[0].startingY);
    file.close();
   

   
    
    // Print the board
    for (int i = 0; i < HEIGHT ; i++) {
       
        for (int j = 0; j < WIDTH +1 ; j++) {
            
            cout << board[i][j];

           
          /*
            if (board[i][j] == 'x') {
                printColoredChar('x', "\033[97m");
            }
            if (board[i][j] == '&') {
                printColoredChar('&', "\033[31m");
            }
            if (board[i][j] == '@') {
                printColoredChar('@', "\033[31m");
            }
            if (board[i][j] == 'H') {
                printColoredChar('H', "\033[38;5;94m");
            }



            if (board[i][j] == 'L' || board[i][j] == ' '  || board[i][j] == 'Q' || board[i][j] == '='|| board[i][j] == '<' ||  board[i][j] == '>' || board[i][j] == 'p' || board[i][j] == '$') {
                cout << board[i][j];
            }
           */
           
           
            /*if (board[i][j] == 'x')
            {
                ghosts.push_back(Ghost(i, j, 3));
            }*/
        }
        cout << endl;  // Move to the next line after printing each row
    }
    
    
    return true;
}

/*// Check if Mario reaches Pauline
bool TheDonkykongGame::checkWinCondition() {
    return (marioX == paulineX && marioY == paulineY);
}
*/

// Transition to the next level



//bool TheDonkykongGame::checkWinCondition() const {
  //  return (m[0].reached  == paulineX && mario.getY() == paulineY);
//} 

void TheDonkykongGame::nextLevel() {
   
    //delete m;
    ghosts.clear();
    barrels.clear();
    currentLevel++;
    if (currentLevel < screens.size()) {
        if (!loadLevel(screens[currentLevel])) {
            cerr << "Failed to load next level!" << endl;
            exit(1); // Exit the game on failure
        }
       
        //m[0].resetPosition(m[0].startingX , m[0].startingY);

        
       // m[0].resetPosition();

    }
    else {
        cout << "Congratulations! You completed all levels!"  << endl;
        printf("Your score was : %d", m[0].score);
        m[0].marioWon = true;
        //exit(0); // End the game after the last level
    }
}

// Run the game loop
void TheDonkykongGame::run() {
    
    char key = 0;
    int dir ;
   

    do {
        if (_kbhit()) {
            key = _getch();
            if ((dir = m[0].getDirection(key)) != -1)
            {
                m[0].setDirection(dir);
                
            }
            else if (key == 'p' || key == 'P')
            {
                if (m[0].setHammer())
                {
                    m[0].setAttack(true);
                    
                }
            }
        }
        
        m[0].move(); // Move Mario

        //spawnGhosts();
        barrelSpawnTimer++;
        if (barrelSpawnTimer >= 53)
        {
            spawnBarrel(monkeyX, monkeyY);
            barrelSpawnTimer = 0;
        }
        
        updateSGhosts();
        updateGhosts();
        updateBarrels();

       
        // Check win condition
        if (m[0].reached == true) {
            cout << "You reached Pauline!" << endl;
            nextLevel(); // Load next level
        }

        Sleep(75); // Game speed
    } while (key != ESC);
}

// Initialize the game
void TheDonkykongGame::init() {
    system("cls");

    srand(time(0));
    if (screens.empty()) {
        cerr << "No level files found!" << endl;
        exit(1);
    }

    if (!loadLevel(screens[currentLevel])) {
        cerr << "Failed to load initial level!" << endl;
        exit(1);
    }
}

void TheDonkykongGame::loadSteps(const std::string& stepsFile) {
    std::ifstream file(stepsFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open steps file: " << stepsFile << std::endl;
        return;
    }

    steps.clear(); // Clear any existing steps data.
    int timePoint , dir;
    std::string objectId, action;

    std::string firstWord;
    file >> firstWord;
    if (firstWord == "SEED") {
        int seed;
        file >> seed;
        srand(seed);  // Apply the same seed used when saving
      
    }
    else {
        // If there's no seed, move file pointer back
        file.seekg(0);
    }


    
    while (file >> timePoint >> objectId >> action >> dir) {
        steps.emplace_back(timePoint, objectId, action, dir); // Store steps as tuples or custom structs.
       
    }

    file.close();
    std::cout << "Steps loaded successfully from " << stepsFile << std::endl;
}
/*void TheDonkykongGame::runReplay() {
    int currentTime = 0;
    for (const auto& step : steps) {
        int timePoint = std::get<0>(step);
        const std::string& objectId = std::get<1>(step);
        const std::string& action = std::get<2>(step);
        int dir = std::get<3>(step);

      


        // Wait until the correct time point
        //if (currentTime < timePoint) {
        while (currentTime < timePoint) {
            
            executeAction(objectId, action, dir);
           
            m[0].move();
            
            barrelSpawnTimer++;
            if (barrelSpawnTimer >= 53) {
                spawnBarrel(monkeyX, monkeyY);
                barrelSpawnTimer = 0;
            }

            // Update game state
            updateSGhosts();
            updateGhosts();
            updateBarrels();
            //updateGame(); // Update game state (e.g., barrels, enemies)
            //renderGame(); // Render the game to the screen
            //Sleep(50);    // Simulate game loop delay
            Sleep(75);
            ++currentTime;
            //}

            // Execute the action for the object
           
        }
    }
}*/
void TheDonkykongGame::runReplay() {
    int currentTime = 0;
    for (const auto& step : steps) {
        int timePoint = std::get<0>(step);
        const std::string& objectId = std::get<1>(step);
        const std::string& action = std::get<2>(step);
        int dir = std::get<3>(step);

        // Wait until the correct time point
        while (currentTime < timePoint) {
            m[0].move();

            barrelSpawnTimer++;
            if (barrelSpawnTimer >= 53) {
                spawnBarrel(monkeyX, monkeyY);
                barrelSpawnTimer = 0;
            }

            // Update game state
            updateSGhosts();
            updateGhosts();
            updateBarrels();

            Sleep(75);
            ++currentTime;
        }

        // Now execute the action at the correct time
        executeAction(objectId, action, dir);
    }
}


void TheDonkykongGame::runSilent(const std::string& resultsFile) {
    int currentTime = 0;
    for (const auto& step : steps) {
        int timePoint = std::get<0>(step);
        const std::string& objectId = std::get<1>(step);
        const std::string& action = std::get<2>(step);

        while (currentTime < timePoint) {
            updateGame(); // Update game state without rendering
            ++currentTime;
        }
        int dir = std::get<3>(step);
        // Execute the action
        executeAction(objectId, action,dir);
    }

    // Verify results
    std::ifstream file(resultsFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open results file: " << resultsFile << std::endl;
        return;
    }

    int expectedLivesLost, expectedFinishTime, expectedScore;
    file >> expectedLivesLost >> expectedFinishTime >> expectedScore;

    // Compare the results with the game's current state
    bool passed = (livesLost == expectedLivesLost) &&
        (finishTime == expectedFinishTime) &&
        (score == expectedScore);

    if (passed) {
        std::cout << "Test passed!" << std::endl;
    }
    else {
        std::cout << "Test failed! Mismatch in results." << std::endl;
        std::cout << "Expected: Lives=" << expectedLivesLost
            << ", FinishTime=" << expectedFinishTime
            << ", Score=" << expectedScore << std::endl;
        std::cout << "Actual:   Lives=" << livesLost
            << ", FinishTime=" << finishTime
            << ", Score=" << score << std::endl;
    }

    file.close();
}


void TheDonkykongGame::runAndSave(const std::string& stepsFile, const std::string& resultsFile) {
    
    int levelCounter = 1; // Start at level 1

    std::ofstream stepsOut(stepsFile);
    std::ofstream resultsOut(resultsFile);

    if (!stepsOut.is_open() || !resultsOut.is_open()) {
        std::cerr << "Error: Unable to open save files!" << std::endl;
        return;
    }
    int seed = time(0);
    srand(seed);
    stepsOut << "SEED " << seed << std::endl;
    int currentTime = 0;
    char key = 0;
    int dir;
    int barrelSpawnTimer = 0; // Ensure this is tracked

    while (m[0].lives > 0) {
        // Handle player input
        if (_kbhit()) {
            key = _getch();
            if ((dir = m[0].getDirection(key)) != -1) {
                m[0].setDirection(dir);
            }
            else if (key == 'p' || key == 'P') {
                if (m[0].setHammer())
                {
                    m[0].setAttack(true);

                }
            }
        }

        // Move Mario
        
        m[0].move();

        // Barrel spawning logic
        barrelSpawnTimer++;
        if (barrelSpawnTimer >= 53) {
            spawnBarrel(monkeyX, monkeyY);
            barrelSpawnTimer = 0;
        }

        // Update game state
        updateSGhosts();
        updateGhosts();
        updateBarrels();

        // Render game
        //renderGame();

        // Log steps
        for (const auto& step : getRelevantSteps(currentTime)) {
            stepsOut << currentTime << " " << step.objectId << " " << step.action << " " << step.direction << std::endl;
        }

        // Check win condition
        if (m[0].reached == true) {
            cout << "You reached Pauline!" << endl;
            
            nextLevel();
            stepsOut.close();
            levelCounter++;
            string newLevel = "level%d.steps.txt", levelCounter;
            std::ofstream stepsOut(newLevel);
        }
      
       /* if (m[0].reached == true) {
            cout << "You reached Pauline!" << endl;
            nextLevel();

            // Close current steps file
            stepsOut.close();

            // Open new steps file for the next level
            levelCounter++;
            std::string newStepsFile = "steps_level_" + std::to_string(levelCounter) + ".txt";
            stepsOut.open(newStepsFile);
            if (!stepsOut.is_open()) {
                std::cerr << "Error: Unable to open new steps file!" << std::endl;
                return;
            }
            stepsOut << "SEED " << seed << " LEVEL " << levelCounter << std::endl;
        }*/


        Sleep(75);
        ++currentTime;
    }

    // Save results at the end
    
    if (m[0].reached || m[0].lives < 1)
    {
        resultsOut << "Lives :" << m[0].lives << std::endl << "Time : " << currentTime << std::endl << "Score: " << m[0].score << std::endl;
    }
    

    stepsOut.close();
    resultsOut.close();
}






void TheDonkykongGame::updateGame() {
    //spawnGhosts();
    //spawnGhosts();
    updateGhosts();
    updateBarrels();
}

void TheDonkykongGame::renderGame() {
    std::ostringstream buffer; // Use string buffer instead of directly printing

    // Build the board in the buffer
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            buffer << board[i][j];
        }
        buffer << "\n";
    }

    // Print everything at once to prevent flickering
    std::cout << buffer.str();
}



void TheDonkykongGame::executeAction(const std::string& objectId, const std::string& action , int dir) {
   

    if (objectId == "Mario" && action == "HAMMER" && ((dir ==2) || (dir == 3)))
    {
        m[0].hammer = true;
        
        
    }
    if (objectId == "Mario" && action == "ATTACK" && ((dir == 2) || (dir == 3)))
    {
        m[0].attack = true;
        

    }
    if (objectId == "Mario" && action == "MOVE" && dir ==2 )
    {
        m[0].setDirection(2);
        
        
       
    }
    if (objectId == "Mario" && action == "MOVE" && dir == 3)
    {
        m[0].setDirection(3);
        
    }
    if (objectId == "Mario" && action == "MOVE" && dir == 1)
    {
        m[0].setDirection(1);

       
    }
    if (objectId == "Mario" && action == "MOVE" && dir == 0)
    {
        m[0].setDirection(0);

        
    }
    // Add more logic for other objects and actions
}

bool TheDonkykongGame::isGameOver() const {
    return (m[0].getLives() <= 0 || currentLevel >= screens.size());
}




