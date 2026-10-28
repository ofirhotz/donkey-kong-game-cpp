#pragma once
#ifndef BARREL_H
#define BARREL_H
#include <vector>

class Barrel {
protected:
    int x, y;            // Barrel position
    char savedChar;      // Character saved under the barrel
    int fallCounter;     // Tracks how far the barrel has fallen
    int direction;       // 2: LEFT, 3: RIGHT

public:

    bool metMario = false;
    bool atacked = false;
    // Constructor
    Barrel(int startX, int startY, int dir);

    // Moves the barrel based on gravity and platform direction
    void move();

    // Handles the explosion logic (clears the barrel from the screen)
    void explode();

    // Draw the barrel at the new position
    void drawAtNewPosition(int newX, int newY, char symbol = 'O');

    bool checkCollision(int marioX, int marioY) const;

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }


};

#endif

