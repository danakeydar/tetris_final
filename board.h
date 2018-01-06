#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <stdio.h>  
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include "shape.h"
#include "game.h"

class Board {
public:
	enum { WIDTH = 10, endOfBoard = 19 };

	bool gameOver(const Shape& p)
	{
		if (board[p.body[0].y][p.body[0].x] == true || board[p.body[1].y][p.body[1].x] == true || board[p.body[2].y][p.body[2].x] == true || board[p.body[3].y][p.body[3].x] == true)
			return true;
		else
			return false;
	}
	Board(); //board c'tor 
	static bool board[20][10];
	void updateBoard(const Shape& p);
	bool isPossibleMove(const Shape& p, char keyPressed);
	void updateBoardAfterDelete(int y);
	void deleteRow(int y);
	void checkForFullRows(const Shape& p);
	void deleteBombArea(const Shape& p);

};
#endif