#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

class Point {
	int x = 8, y = 25;
public:
	void draw(char ch);
	void draw2(char ch, int x, int y);
	void move(int direction);
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int newX) { x = newX; }
    void setY(int newY){y = newY;}

};

#endif