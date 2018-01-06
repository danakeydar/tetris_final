#ifndef _GAME_H_
#define _GAME_H_

#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>  
#include "utils.h"
#include "Shape.h"
#include "Board.h"

using namespace std;

enum KEYS { NEW_GAME = '1', PAUSE = '2', CONTINUE = '3', SPEED_UP = '4', SPEED_DOWN = '5', EXIT = '6' }; 
enum speed { HARD_DROP_SPEED = 80, SOFT_DROP_SPEED = 150 };

class Game {
	 void menu()
	{
		 //placed the menu buttons in a specific location of the screen
		gotoxy(1, 1); 
		cout << "Score : " << score;
		gotoxy(30, 5);     cout << "1 - New game " << endl;
		gotoxy(30, 6);    cout << "2 - Pause  " << endl;
		gotoxy(30, 7);    cout << "3 - Continue  " << endl;
		gotoxy(30, 8);    cout << "4 - Speed up " << endl;
		gotoxy(30, 9);    cout << "5 - Speed down " << endl;
		gotoxy(30, 10);   cout << "6 - Exit " << endl;

	}
	 void drawBoardFrame();
	 void printGameOver()
	{
		gotoxy(1, 4);
		cout << "game over!";
	}

public:
	Game()
	{
	score = 0;
	menu();
	drawBoardFrame();
	}
	static unsigned int score;
	static void updateScore(char ch);
	void run();
};

#endif