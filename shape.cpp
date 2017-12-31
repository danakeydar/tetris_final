#include "Shape.h"
#include "board.h"

void Shape::rotateLine()
{
	if (SType == LINE)
	{
		if (body[0].y == body[1].y)
		{
			body[1].x = body[2].x = body[3].x = body[0].x;
			body[1].y = body[0].y - 1;
			body[2].y = body[1].y - 1;
			body[3].y = body[2].y - 1;

			draw();
		}
		else
		{
			body[3].y = body[2].y = body[1].y = body[0].y;
			body[1].x = body[0].x + 1;
			body[2].x = body[1].x + 1;
			body[3].x = body[2].x + 1;
		}
	}
}

Shape::Shape(const Point& head) {

	setShapeType();

	body[0] = head;
	if (SType == SQUARE) {
		c = '*';
		body[1] = head.right();
		body[2] = head.down();
		body[3] = body[2].right();
	}
	else if (SType == LINE) {
		c = '*';
		body[1] = head.right();
		body[2] = body[1].right();
		body[3] = body[2].right();
	}
	else if (SType == JOKER)
	{
		body[1] = head;
		body[2] = head;
		body[3] = head;

		c = '*';
	}
	else
	{
		body[1] = head;
		body[2] = head;
		body[3] = head;
		c = '@';
	}
}

void Shape::move(char keyPressed)
{
	if (SType != JOKER)
		draw(' ');
	else
	{
		if (Board::board[body[0].y][body[0].x] == false)
			draw(' ');
	}

	if (keyPressed == Direction::SOFT_DROP || keyPressed == Direction::DOWN || keyPressed == Direction::RIGHT || keyPressed == Direction::LEFT)
	{
		for (auto& p : body) {
			p.move(keyPressed);
		}
		if (SType != JOKER)
			draw();
		else
		{
			if (Board::board[body[0].y][body[0].x] == false)
				draw();
		}

	}
	else if (keyPressed == Direction::ROTATE)
		rotateLine();

}

void Shape::draw(char ch)
{
	for (const auto& p : body)
	{
		p.draw(ch);
	}
}

