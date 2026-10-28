#ifndef GHOSTS_H
#define GHOSTS_H

#include "Barrels.h"
class SGhosts : public Barrel
{
private:

    void drawAtNewPosition2(int newX, int newY, char symbol = 'X');

public:
    // Constructor
    SGhosts(int startX, int startY, int dir);

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }

    // Override move method for ghost-specific behavior
    void move();

    // Check if the ghost is on a valid floor tile
    bool isValidFloorTile(int nextX, int nextY);

    void changeDirection();
    int getRandomNumber();
    bool checkBarrelCol();
    bool checkMarioCol();
    bool checkSG();
    bool hasFivePercentChance();

};
#endif


