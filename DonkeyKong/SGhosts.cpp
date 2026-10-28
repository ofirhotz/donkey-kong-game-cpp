#include "SGhosts.h"

#include "io_utils.h" // Include utility functions like `getCharAt`, `gotoxy`
#include <iostream>
#include <unordered_set>


using namespace std;



// Constructor
SGhosts::SGhosts(int startX, int startY, int dir)
    : Barrel(startX, startY, dir) {
}

void SGhosts::drawAtNewPosition2(int newX, int newY, char symbol) {
    
    // Restore the saved character
    gotoxy(x, y);
    if (getCharAt(x, y) != 'O' ) { // Only overwrite if it's still the barrel
        cout << savedChar;
        
        

    }
    // cout << savedChar;

     // Save the character at the new position
    savedChar = getCharAt(newX, newY);
    if (savedChar == 'X')
    {
        return;
    }
    // Update position
    x = newX;
    y = newY;

    // Draw the barrel
    gotoxy(x, y);
    cout << symbol;
}

// Override move method
void SGhosts::move() {
   
    int currX = x;
    int currY = y;
    bool met = false;
    

    // Gravity: Check if the barrel needs to fall



   // if (hasFivePercentChance() == true)
    //{
     //   changeDirection();
    //}

    if (getCharAt(x, y + 1) == ' ') {

        changeDirection();

    }

    if (checkSG())
    {
        met = true;
    }
   
    //(getCharAt(x, y + 1) != ' ')

        // Handle horizontal movement (left or right)
    switch (direction) {
    case 1: currY--; break;// Move UP
    case 2: currX--; break; // Move LEFT
    case 3: currX++; break; // Move RIGHT
    }

    int currDir = direction;

    // Check for direction changes (follow platform directions)
    //if (getCharAt(nextX, nextY) == '<') direction = 2;  // Move LEFT
    //if (getCharAt(nextX, nextY) == '>') direction = 3;  // Move RIGHT
    /*if (getCharAt(nextX, nextY) == 'O')
    {
        printf("fdgfdgdfgdf");
    }*/

    if (checkBarrelCol() || checkMarioCol() )
    {
        //changeDirection();
        return;
    }

     if (getCharAt(currX, currY) == '=' || getCharAt(currX, currY) == ' ' || getCharAt(currX, currY) == 'x' ) 
     {
        // Continue in the current direction (ignore ladders but let the barrel keep moving)

    }

    else if (getCharAt(currX,currY) == 'H')// || getCharAt(nextX, nextY - 1) == 'H')
     {
         
       
             direction = 1;
             if (getCharAt(currX, currY - 1) == ' ')
             {
                 direction = 3;
             }
             if (getCharAt(currX, currY + 1) == 'H')
             {
                 direction = currDir;
             }
         

        
    }
    else {

         if (!met)
         {
             changeDirection();
             return;
         }
    }



    // Check if the barrel has fallen too far (e.g., 8 rows max)
   /* if (fallCounter >= 8) {
        explode();
        return;
    }*/

    // Draw the barrel at the new position

    drawAtNewPosition2(currX, currY);



}

// Helper function to check if the ghost is on a valid floor tile
/*bool Ghost::isValidFloorTile(int nextX, int nextY) {
    char nextTile = getCharAt(nextX, nextY); // Check the tile at the ghost's next position
    return (nextTile == '=' || nextTile == '<' || nextTile == '>');
}*/

void SGhosts::changeDirection() {
    direction = (direction == 2) ? 3 : 2;  // Reverse direction: 2 -> 3 (left to right), 3 -> 2 (right to left)
}

bool SGhosts::checkBarrelCol()
{

    int nextX = x;
    int nextY = y;

    if (getCharAt(nextX + 1, nextY) == 'O')
    {
        return true;
    }
    if (getCharAt(nextX - 1, nextY) == 'O')
    {
        return true;
    }
    if (getCharAt(nextX, nextY + 1) == 'O')
    {
        return true;
    }
    if (getCharAt(nextX, nextY - 1) == 'O')
    {
        return true;
    }
    if (getCharAt(nextX, nextY) == 'O')
    {
        return true;
    }

    return false;
}
bool SGhosts::checkMarioCol()
{
    int nextX = x;
    int nextY = y;
    if (getCharAt(nextX + 1, nextY) == '@')
    {
        return true;
    }
    if (getCharAt(nextX - 1, nextY) == '@')
    {
        return true;
    }
    if (getCharAt(nextX, nextY + 1) == '@')
    {
        return true;
    }
    if (getCharAt(nextX, nextY - 1) == '@')
    {
        return true;
    }
    if (getCharAt(nextX, nextY) == '@')
    {
        return true;
    }

    return false;
}

bool SGhosts::checkSG()
{
    int nextX = x;
    int nextY = y;
    if (getCharAt(nextX + 1, nextY) == 'X')
    {
        return true;
    }
    if (getCharAt(nextX - 1, nextY) == 'X')
    {
        return true;
    }
    if (getCharAt(nextX, nextY + 1) == 'X')
    {
        return true;
    }
    if (getCharAt(nextX, nextY - 1) == 'X')
    {
        return true;
    }
    if (getCharAt(nextX, nextY) == 'X')
    {
        return true;
    }

    return false;
}
int SGhosts :: getRandomNumber() 
{
    std::srand(std::time(0)); // Seed the RNG
    return (std::rand() % 100) + 1; // Random number between 1 and 100
}

bool SGhosts::hasFivePercentChance()
{

    int num = getRandomNumber();

    // Define a set of "lucky" numbers
    std::unordered_set<int> luckyNumbers = { 23, 8, 10, 30, 11 };

    // Check if the number is in the set
    return luckyNumbers.find(num) != luckyNumbers.end();

}
