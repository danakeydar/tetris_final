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
	Board() //board c'tor 
	{
		for (int i = 4;i <= endOfBoard;i++)
		{
			for (int j = 0;j < WIDTH;j++)
			{
				board[i][j] = false;
			}
		}
	}
	static bool board[20][10];
	void updateBoard(const Shape& p)
	{
		for (int i = 0;i < 4;i++)
			board[p.body[i].y][p.body[i].x] = true;
	}
	bool isPossibleMove(const Shape& p, char keyPressed);
	void updateBoardAfterDelete(int y);
	void deleteRow(int y)
	{
		for (int i = 0;i < 10;i++)
		{
			gotoxy(i, y);
			cout << ' ';
			board[y][i] = false;
		}

		updateBoardAfterDelete(y);
	}
	void checkForFullRows(const Shape& p);
	void deleteBombArea(const Shape& p);

};
#endif