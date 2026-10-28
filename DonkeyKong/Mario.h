#ifndef _MARIO_H_
#define _MARIO_H_

#include <cstring>
#include "Point.h"

class Mario {
	enum { SIZE = 1 };
	Point body[SIZE];
	char arrowKeys[5] = {'w' , 'x' ,'a' ,'d' , 's'};
	Signs color;
	
	
	
	
public:
	bool marioWon = false;
	int lives;
	bool hammer = false;
	bool jumping = false;
	bool reached;
	int livesX;
	int livesY;
	int startingX;
	int startingY;
	bool attack = false;
	int score =0;
	int direction = 4;
	
	/*void setArrowKeys(const char* keys) {
		arrowKeys[0] = 'a';
		arrowKeys[1] = 'd';
		arrowKeys[2] = 'w';
		arrowKeys[3] = 'x';
		arrowKeys[4] = 's';

	}*/
	int getX()
	{
		return body[0].getX();
	}
	int getY()
	{
		return body[0].getY();
	}
	void move();
	int getDirection(char key);
	char getCharAt(int x, int y);
	void draw(char symbol); // Declaration

	Mario();
	void setDirection(int dir) {
		direction = dir;
	}
	int getLives() const { return lives; }
	void loseLife();
	void resetPosition(int x, int y);
	bool checkFall();

	const Point& getBody() const { return body[0]; }
	void displayLives() const;  // Display the remaining lives on screen
	bool checkBarrelCollision();

	bool checkKeyPress(char key);
	bool setHammer();
	void destroyNearbyEnemies();
	void setAttack(bool value);


private:
	
	
	//int startX, startY;
	  // Track if Mario is in the middle of a jump

	//std::vector<Point> body;


};

#endif