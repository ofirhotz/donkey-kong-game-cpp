#include "Barrels.h"
#include "io_utils.h" // Include utility functions like `getCharAt`, `gotoxy`
#include <iostream>
#include "Mario.h"

using namespace std;

// Constructor
Barrel::Barrel(int startX, int startY, int dir)
    : x(startX), y(startY), savedChar(' '), fallCounter(0), direction(dir) {
}


// Barrel Explosion Logic
void Barrel::explode() {
    drawAtNewPosition(x, y, ' '); // Clear the barrel
    // Optionally add explosion animation here
}

void Barrel::move() {
    int nextX = x;
    int nextY = y;

    // Gravity: Check if the barrel needs to fall
    if (getCharAt(x, y + 1) == ' ') {
        nextY ++; // Barrel falls
       // gotoxy(85, 2);
        //printf("%d" , nextY);
        fallCounter++;  // Increment fall counter
    }
    else {
        fallCounter = 0; // Reset fall counter if on a platform

        // Handle horizontal movement (left or right)
        switch (direction) {
        case 2: nextX--; break; // Move LEFT
        case 3: nextX++; break; // Move RIGHT
        }
        if (getCharAt(nextX, nextY) == '@')
        {
            metMario = true;
        }
        // Check for direction changes (follow platform directions)
        if (getCharAt(nextX, nextY+1) == '<') direction = 2;  // Move LEFT
        if (getCharAt(nextX, nextY+1) == '>') direction = 3;  // Move RIGHT
        if (getCharAt(nextX, nextY) == '=' || getCharAt(nextX, nextY) == ' ' || getCharAt(nextX, nextY) == 'H' || getCharAt(nextX, nextY) == 'x' || getCharAt(nextX, nextY) == 'X') {
            // Continue in the current direction (ignore ladders but let the barrel keep moving)
        }
        else {
            // If a wall or obstacle is hit, stop or explode
            if (getCharAt(nextX, nextY) == 'Q')
            {
                drawAtNewPosition(nextX, nextY, 'Q');
           }
            
           
           
            return;
        }
    }

    // Check if the barrel has fallen too far (e.g., 8 rows max)
    if (fallCounter >= 8) {
        explode();
        return;
    }

    // Draw the barrel at the new position
    drawAtNewPosition(nextX, nextY);
}

// Draw Barrel at New Position
void Barrel::drawAtNewPosition(int newX, int newY, char symbol) {
    // Restore the saved character
    
        gotoxy(x, y);

        if (getCharAt(x, y) != 'x') { // Only overwrite if it's still the barrel
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

bool Barrel::checkCollision(int marioX, int marioY) const 
{
    return (x == marioX && y == marioY);
}
