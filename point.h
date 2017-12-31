#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "utils.h"
#include "Direction.h"

using namespace std;

class Point
{	
public:
	int x;
	int y;
	Point(int x1=1 , int y1=1 ) {
		x = x1;
		y = y1;
	}
	Point right() const {
		return Point(x + 1, y);
	}
	Point down() const {
		return Point(x, y + 1);
	}
	//used for delete and write the shapes 
	void draw(char c = '*') const {
		gotoxy(x, y);

		cout << c;
		cout.flush();
	}
	void move(char keyPressed)
	{

		switch (keyPressed) {
		case Direction::LEFT:
			x--;
			break;
		case Direction::RIGHT:
			x++;
			break;
		case Direction::DOWN:
			y++;
			break;
		}
	}
};


#endif
