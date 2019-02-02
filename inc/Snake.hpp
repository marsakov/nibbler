#pragma once

#include <iostream>
#include <vector>
#include "Rect.hpp"

class Snake
{

public:
	int						SCREEN_WIDTH;
	int						SCREEN_HEIGHT;

	std::vector<rect>		snakeRECT;
	char					direction;
	int						snakeSize;
	rect					appleRECT;
	rect					pieceRECT;

	Snake(int width, int height);
	Snake(Snake &obj);
	~Snake();

	bool	moveSnake();
	void	generateApple();
	bool	checkCollision();	

};