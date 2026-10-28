#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#include "Signs.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
//void setTextColor(Color);
void hideCursor();
void clear_screen();
void gotoxy2(int x, int y);
char getCharAt(int x, int y);
void gameOver(const std::string& message);

#endif