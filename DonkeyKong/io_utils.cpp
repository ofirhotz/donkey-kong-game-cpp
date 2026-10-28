#include "io_utils.h"
#include "Signs.h"

using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout<<flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

/*void setTextColor(Color colorToSet) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}*/

void hideCursor()
{
	 HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO CURSOR;
	 CURSOR.dwSize = 1;
	 CURSOR.bVisible = FALSE;
	 SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void clear_screen()
{
	system("cls");
}
void gotoxy2(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char getCharAt(int x, int y) {
	CHAR_INFO ci;
	COORD size = { 1, 1 };
	COORD pos = { 0, 0 };
	SMALL_RECT rect = { x, y, x, y };
	ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, size, pos, &rect);
	return ci.Char.AsciiChar;
}

void gameOver(const std::string& message) {
	system("cls");
	std::cout << message << std::endl;
	std::cout << "Game Over!" << std::endl;
	exit(0);
}





