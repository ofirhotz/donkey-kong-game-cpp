#ifndef GHOST_H
#define GHOST_H

#include "Barrels.h"

// Ghost class, derived from Barrel
class Ghost : public Barrel {
private:

    void drawAtNewPosition2(int newX, int newY, char symbol = 'x');

public:
    // Constructor
    Ghost(int startX, int startY, int dir);

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

    void setSeed(int seed);
    // Check if the ghost is on a valid floor tile
    bool isValidFloorTile(int nextX, int nextY);

    void changeDirection();

    bool SGCol();
    bool checkBarrelCol();
    bool checkMarioCol();
    bool hasFivePercentChance();


};

#endif // GHOST_H
