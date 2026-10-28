#include "Ghosts.h"
#include "io_utils.h" // Include utility functions like `getCharAt`, `gotoxy`
#include <iostream>
#include <unordered_set>

using namespace std;



// Constructor
Ghost::Ghost(int startX, int startY, int dir)
    : Barrel(startX, startY, dir) {
}

void Ghost::drawAtNewPosition2(int newX, int newY, char symbol) {
    // Restore the saved character
   
    
    gotoxy(x, y);
    if (getCharAt(x, y) != 'O') { // Only overwrite if it's still the barrel
        cout << savedChar;
    }
   // cout << savedChar;

    // Save the character at the new position
    savedChar = getCharAt(newX, newY);
    
    
    

    // Update position
    x = newX;
    y = newY;

    // Draw the barrel
    gotoxy(x, y);
    cout << symbol;
}
// Override move method
void Ghost::move() {
    int nextX = x;
    int nextY = y;
    bool edge = false;

    // Gravity: Check if the barrel needs to fall


    
    if (hasFivePercentChance() == true)
    {
        changeDirection();
    }

    if (getCharAt(x, y + 1) == ' ') {
       
        changeDirection();  
           
    }
    if (getCharAt(nextX+1, nextY) == 'x') {

        changeDirection();
        

    }
    //(getCharAt(x, y + 1) != ' ')

        // Handle horizontal movement (left or right)
        switch (direction) {
        case 2: nextX--; break; // Move LEFT
        case 3: nextX++; break; // Move RIGHT
        }

        // Check for direction changes (follow platform directions)
        //if (getCharAt(nextX, nextY) == '<') direction = 2;  // Move LEFT
        //if (getCharAt(nextX, nextY) == '>') direction = 3;  // Move RIGHT
        /*if (getCharAt(nextX, nextY) == 'O')
        {
            printf("fdgfdgdfgdf");
        }*/
       
        if (checkBarrelCol() || checkMarioCol())
        {
            //changeDirection();
            return;
        }

        if (SGCol())
        {
            return;
        }

      
         if (getCharAt(nextX, nextY) == '=' || getCharAt(nextX, nextY) == ' ' || getCharAt(nextX, nextY) == 'H') {//|| checkBarrel()){// || getCharAt(nextX, nextY) == 'O') {
            // Continue in the current direction (ignore ladders but let the barrel keep moving)
        }
        else {
            
            changeDirection();
            
             
        }
    
   

    // Check if the barrel has fallen too far (e.g., 8 rows max)
   /* if (fallCounter >= 8) {
        explode();
        return;
    }*/

    // Draw the barrel at the new position
       
             drawAtNewPosition2(nextX, nextY);
         
         
   
}

// Helper function to check if the ghost is on a valid floor tile
/*bool Ghost::isValidFloorTile(int nextX, int nextY) {
    char nextTile = getCharAt(nextX, nextY); // Check the tile at the ghost's next position
    return (nextTile == '=' || nextTile == '<' || nextTile == '>');
}*/

void Ghost::changeDirection() {
    direction = (direction == 2) ? 3 : 2;  // Reverse direction: 2 -> 3 (left to right), 3 -> 2 (right to left)
}

bool Ghost::SGCol()
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
bool Ghost::checkBarrelCol()
{
     
    
    int nextX = x;
    int nextY = y;
    if (getCharAt(nextX+1, nextY) == 'O')
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
    if (getCharAt(nextX, nextY-1) == 'O')
    {
        return true;
    }
    if (getCharAt(nextX , nextY) == 'O')
    {
        return true;
    }

    return false;
}
bool Ghost::checkMarioCol()
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

static int gameSeed = 42;

void setSeed(int seed) {
    gameSeed = seed;
    std::srand(gameSeed); // Initialize RNG with the same seed
}
int getRandomNumber() {
    return (std::rand() % 100) + 1;
}

bool Ghost::hasFivePercentChance() {
    return getRandomNumber() <= 5; // 5% chance (1-5 out of 100)
}
