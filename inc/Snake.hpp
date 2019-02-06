#pragma once

#include <iostream>
#include <vector>
#include "Rect.hpp"

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
	int						SCREEN_WIDTH;
	int						SCREEN_HEIGHT;

	std::vector<rect>		snakeRECT;
	char					direction;
	int						snakeSize;
	int						snakeStep;
	rect					appleRECT;
	rect					pieceRECT;

	Snake(int width, int height);
	Snake(Snake &obj);
	~Snake();

	void	choseDirection(eKeyType key);
	bool	moveSnake();
	void	generateApple();
	bool	checkCollision();

};