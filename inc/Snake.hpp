#pragma once

#include <iostream>
#include <vector>

typedef struct	rect
{
	int		x;
	int		y;
	double	w;
	double	h;

}				rect;


enum eKeyType
{
	up,
	down,
	left,
	right,
	escape,
	enter,
	num1,
	num2,
	num3,
	none
};

class Snake
{

public:
	int						screenWidth;
	int						screenHeiht;
	std::vector<rect>		snakeRect;
	char					direction;
	int						size;
	int						step;
	rect					pieceRect;

	Snake(int width, int height);
	Snake(Snake &obj);
	~Snake();

	void	choseDirection(eKeyType key);
	bool	moveSnake();

};