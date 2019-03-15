#include "../inc/Snake.hpp"

Snake::Snake(int width, int height) {
	direction = 'R';
	size = 4;
	step = 50;

	screenWidth = width;
	screenHeiht = height;
	key = right;

	pieceRect.x = width / 100 * 50 + 50;
	pieceRect.y = height / 100 * 50;
	pieceRect.w = 50;
	pieceRect.h = 50;
	snakeRect.push_back(pieceRect);
	for (int i = 0; i < 3; i++)
	{
		pieceRect.x -= 50;
		snakeRect.push_back(pieceRect);
	}
	waiting = false;
}

Snake::Snake(Snake &obj) {
	*this = obj;
}

Snake::~Snake() {

}

void	Snake::choseDirection(eKeyType keyType) {
	switch( keyType )
	{
		case (up):			(direction != 'D') ? direction = 'U' : 0; break ;
		case (down):		(direction != 'U') ? direction = 'D' : 0; break ;
		case (left):		(direction != 'R') ? direction = 'L' : 0; break ;
		case (right):		(direction != 'L') ? direction = 'R' : 0; break ;
		case (w):			(direction != 'D') ? direction = 'U' : 0; break ;
		case (s):			(direction != 'U') ? direction = 'D' : 0; break ;
		case (a):			(direction != 'R') ? direction = 'L' : 0; break ;
		case (d):			(direction != 'L') ? direction = 'R' : 0; break ;
		default : break ; 
	}
}

bool 	Snake::moveSnake() {

	choseDirection(key);

	bool moveLastPiece = true;
	
	if (snakeRect.size() != size) {
		moveLastPiece = false;
		pieceRect.x = snakeRect[snakeRect.size() - 1].x;
		pieceRect.y = snakeRect[snakeRect.size() - 1].y;
		pieceRect.w = snakeRect[snakeRect.size() - 1].w;
		pieceRect.h = snakeRect[snakeRect.size() - 1].h;
	}

	for (int i = snakeRect.size() - 1; i > 0; i--) {
		snakeRect[i].x = snakeRect[i - 1].x;
		snakeRect[i].y = snakeRect[i - 1].y;
		snakeRect[i].w = snakeRect[i - 1].w;
		snakeRect[i].h = snakeRect[i - 1].h;
	}

	switch (direction)
	{
		case 'U':
		{
			if (snakeRect[0].y <= 50)
				return (false);
			snakeRect[0].y -= step;
			break ;
		}
		case 'D':
		{
			if (snakeRect[0].y >= screenHeiht - 100)
				return (false);
			snakeRect[0].y += step;
			break ;
		}
		case 'L':
		{
			if (snakeRect[0].x <= 50)
				return (false);
			snakeRect[0].x -= step;
			break ;
		}
		case 'R':
		{
			if (snakeRect[0].x >= screenWidth - 100)
				return (false);
			snakeRect[0].x += step;
			break ;
		}
	}

	if (!moveLastPiece)
		snakeRect.push_back(pieceRect);
	return (true);
}
