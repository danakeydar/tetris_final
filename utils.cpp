
#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
}
 