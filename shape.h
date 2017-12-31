#ifndef _SHAPE_H_
#define _SHAPE_H_

#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>  
#include <time.h>
#include "Point.h"
#include "Direction.h"

class Shape {
public:
	enum ShapeType { SQUARE, LINE, JOKER, BOMB };
	Point body[4];
	int SType;
private:
	void setShapeType()
	{
		srand((unsigned int)time(NULL));//creating rand shape
		SType = rand() % 100;
		if (0 <= SType&&SType < 30)
			SType = SQUARE;
		else if (30 <= SType&&SType < 60)
			SType = LINE;
		else if (60 <= SType&&SType < 80)
			SType = JOKER;
		else
			SType = BOMB;

	}
	char c;
public:

	Shape(const Point& head);

	void move(char keyPressed);
	void rotateLine();
	void draw(char ch);
	void draw() { draw(c); }

};
#endif