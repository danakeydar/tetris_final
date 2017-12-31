#include "Game.h"
#include "shape.h"
#include "Board.h"

unsigned int Game::score = 0;

void Game::updateScore(char ch)
{
	//the function updating the player score according to the game rules and printing it
	if (ch == SOFT_DROP)
		score = score + 1;
	else if (ch == HARD_DROP)
		score = score + 2;
	else if (ch == 1)
		score = score + 100;
	else if (ch == 2)
		score = score + 300;
	else if (ch == 3)
		score = score + 500;

	gotoxy(1, 1);
	cout << "Score : " << score;

}

void Game::run() {

	Board gameBoard;

	char keyPressed = 0;
	unsigned int speed = 500;
	bool dropDown = false, softDrop = false;

	keyPressed = _getch();
	
	if (keyPressed == KEYS::NEW_GAME)
	{

 		while (keyPressed != EXIT)
		{
			Shape p = { { 4,4 } };//creating a new shape

			if (gameBoard.gameOver(p))
			{
				printGameOver();
				Sleep(500);
				break;
			}
			else
				p.draw();
			while (gameBoard.isPossibleMove(p, 0))//while move down is possible
			{
				if (_kbhit()) {
					keyPressed = _getch();

				if (keyPressed == KEYS::EXIT) { break; }
					else if (keyPressed == KEYS::PAUSE)
					{
						while (keyPressed != CONTINUE)
						{
							if (_kbhit())
								keyPressed = _getch();
						}
					}
					else if (keyPressed == KEYS::SPEED_UP) {
						speed = speed - 50;
					}
					else if (keyPressed == KEYS::SPEED_DOWN)
					{
						speed = speed + 50;
					}
					else if (keyPressed == Direction::HARD_DROP)
					{
						dropDown = true;
					}
					else if (keyPressed == Direction::STOP_JOKER)
					{
						if (p.SType == Shape::JOKER)
							break;
					}
					else
					{
						keyPressed = _getch();//another getch for dealing with the arrows special code

						if (keyPressed == Direction::SOFT_DROP)
						{
							softDrop = true;
							Game::updateScore(SOFT_DROP);
						}
						else
						{
							if (gameBoard.isPossibleMove(p, keyPressed))
								p.move(keyPressed);
						}
					}
				}
				else
				{
					keyPressed = 0;

					if (dropDown == true)
					{
						score++;//correction for the first move
						Game::updateScore(HARD_DROP);
						Sleep(HARD_DROP_SPEED);
					}
					else if (softDrop == true)
						Sleep(SOFT_DROP_SPEED);
					else
						Sleep(speed);

					softDrop = false;

					if (gameBoard.isPossibleMove(p, keyPressed))
						p.move(keyPressed);
				}

			}

			if (keyPressed != EXIT)
			{
				if (p.SType == Shape::BOMB)
					gameBoard.deleteBombArea(p);
				else
					gameBoard.updateBoard(p);

				gameBoard.checkForFullRows(p);
				dropDown = false;
			}
		}

	}
}