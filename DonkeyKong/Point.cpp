#include "Point.h"


void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}

void Point::draw2(char ch, int x1, int y1)
{
	gotoxy(x1, y1);
	cout << ch << endl;
}




void Point::move(int dir) {
	switch (dir) {
	case 0: // UP
		--y;
		if (y < 1) {
			y = 1;
		}
		break;
	case 1: // DOWN
		++y;
		if (y > 25) {
			y = 25;
		}
		break;
	case 2: // LEFT
		--x;
		if (x < 1) {
			x = 1;
		}
		break;
	case 3: // RIGHT
		++x;
		if (x > 80) {
			x = 80;
		}
		break;
	}
}