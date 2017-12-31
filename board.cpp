#include "board.h"

void Board::checkForFullRows(const Shape& p)
{
	int numOfDeletedRows = 0;//to calculate the score

	if (p.SType == Shape::SQUARE)
	{
		for (int j = 0;j <= 2;j=j + 2)
		{
			for (int i = 0;i < 10;i++)
			{
				if (board[p.body[j].y][i] == false)
					break;
				if (i == 9)
				{
					deleteRow(p.body[0].y);
					numOfDeletedRows++;
				}
			}
		}
	}
	else if (p.SType == Shape::LINE)
	{
		if (p.body[0].y == p.body[1].y)//case the line is horizontal
		{
			for (int i = 0;i < 10;i++)
			{
				if (board[p.body[0].y][i] == false)
					break;
				if (i == 9)
				{
					deleteRow(p.body[0].y);
					numOfDeletedRows++;
				}
			}
		}
		else
		{
			int i = 0, counter = 0;
			while (counter<4)//chack all rows of p
			{
				for (int j = 0;j < 10;j++)
				{
					if (board[p.body[0].y - i][j] == false)
						break;
					if (j == 9)
					{
						deleteRow(p.body[i].y);
						numOfDeletedRows++;
						i--;
					}
				}
				i++;
				counter++;
			}
		}
	}
	else if (p.SType == Shape::JOKER)
	{
		for (int j = -1;j <= 1;j++)
		{
			if (p.body[0].y + j >= 0 && p.body[0].y + j < endOfBoard)
			{
				for (int i = 0;i < 10;i++)
				{
					if (board[p.body[0].y + j][i] == false)
						break;
					if (i == 9)
					{
						deleteRow(p.body[0].y);
						numOfDeletedRows++;
					}
				}
			}
		}
	}
	if (numOfDeletedRows>0)
		Game::updateScore(numOfDeletedRows);
}
bool Board::board[20][10] = { false };
void Board::updateBoardAfterDelete(int y)
{
	//the function update the board after deltetion (array and counsole)
	Sleep(400);
	for (int i = y - 1;i >= 0;i--)
	{
		for (int j = 0;j < Board::WIDTH;j++)
		{
			gotoxy(j, i);
			cout << ' ';
			board[i + 1][j] = board[i][j];
			gotoxy(j, i + 1);
			if (board[i + 1][j] == false)
				cout << ' ';
			else
				cout << '*';
			board[i][j] = false;
		}
	}

}
bool Board::isPossibleMove(const Shape& p, char keyPressed)
{
	//the function checks if the wanted move is possible and return true
	//else returning false

	if (keyPressed == 0)//check move down
	{
		if (p.SType == Shape::SQUARE)
		{
			if (((board[p.body[2].y + 1][p.body[2].x] == true) || (board[p.body[3].y + 1][p.body[3].x] == true)) || (p.body[3].y + 1 == endOfBoard))
				return false;
			else
				return true;
		}
		else if (p.SType == Shape::LINE)
		{
			if (p.body[0].y == p.body[1].y)
			{
				if (p.body[0].y + 1 == endOfBoard)
					return false;
				else
				{
					for (int i = 0;i < 4;i++)
					{
						if (board[p.body[i].y + 1][p.body[i].x] == true)
							return false;
					}
					return true;
				}
			}
			else
			{
				if ((board[p.body[0].y + 1][p.body[3].x] == true) || (p.body[0].y + 1 == endOfBoard))
					return false;
				
					return true;
			}
		}
		else if (p.SType == Shape::JOKER)
		{
			if (p.body[0].y + 1 == endOfBoard || keyPressed == 's')
				return false;
			return true;
		}
		else
		{
			if (p.body[0].y + 1 == endOfBoard || board[p.body[0].y + 1][p.body[0].x] == true)
				return false;
			return true;
		}
	}
	else if (keyPressed == Direction::LEFT)
	{
		if (p.body[0].x == 0)//case the shape located in the left border of the board
			return false;
		else if (p.SType == Shape::SQUARE)
		{
			if (board[p.body[0].y][p.body[0].x - 1] == false && board[p.body[2].y][p.body[2].x - 1] == false)
				return true;
			return false;
		}
		else if (p.SType == Shape::LINE)
		{
			if (p.body[0].y == p.body[1].y)
			{
				if (board[p.body[0].y][p.body[0].x - 1] == false)
					return true;
				return false;
			}
			else {
				for (int i = 0; i < 4;i++) {
					if (board[p.body[i].y][p.body[i].x - 1] == true)
						return false;
					return true;
				}
			}
		}
		else
		{
			if (board[p.body[0].y][p.body[0].x - 1] == true)
				return false;
			return true;
		}


	}
	else//case keypressed is right 
	{
		if (p.body[3].x + 1 == WIDTH)//case the shape located in the right border of the board
			return false;
		else if (p.SType == Shape::SQUARE)
		{
			if (board[p.body[1].y][p.body[1].x + 1] == false && board[p.body[3].y][p.body[3].x + 1] == false)
				return true;
			return false;
		}
		else if (p.SType == Shape::LINE)
		{
			if (p.body[0].y == p.body[1].y)
			{
				if (board[p.body[3].y][p.body[3].x + 1] == false)
					return true;
				return false;
			}
			else {
				for (int i = 0; i < 4;i++) {
					if (board[p.body[i].y][p.body[i].x + 1] == true)
						return false;
					return true;
				}
			}
		}
		else
		{
			if (board[p.body[0].y][p.body[0].x + 1] == true)
				return false;
			return true;
		}


	}
}
void Board::deleteBombArea(const Shape& p)
{
	//the function delete 3x3 around the bomb
	int left = 0, right = 0, down = 0, up = 0;

	if (p.body[0].x != 0)
		left = p.body[0].x - 1;
	else
		left = p.body[0].x;

	if (p.body[0].y != 0)
		up = p.body[0].y - 1;
	else
		up = p.body[0].y;

	if (p.body[0].x + 1 != Board::WIDTH)
		right = p.body[0].x + 1;
	else
		right = p.body[0].x;

	if (p.body[0].y + 1 != Board::endOfBoard)
		down = p.body[0].y + 1;
	else
		down = p.body[0].y;

	for (int i = left;i <= right;i++)
	{
		for (int j = up;j <= down;j++)
		{
			gotoxy(i, j);
			cout << ' ';
			Board::board[j][i] = false;
		}
	}
	Sleep(600);

	int k = 0;
	if (p.body[0].y == endOfBoard - 1)
		k = 2;
	else
		k = 3;

	for (int i = p.body[0].y - 2;i >= 0;i--)
	{

		for (int j = p.body[0].x - 1;j <= p.body[0].x + 1;j++)
		{
			board[i + k][j] = board[i][j];
			board[i][j] = false;

			if (board[i + k][j] == true)
			{
				gotoxy(j, i);
				cout << ' ';
				gotoxy(j, i + k);
				cout << '*';
			}
		}

	}


}