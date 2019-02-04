#include "../inc/Snake.hpp"

Snake::Snake(int width, int height) {
	direction = 'R';
	snakeSize = 1;

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	pieceRECT.x = 50;
	pieceRECT.y = 50;
	pieceRECT.w = 50;
	pieceRECT.h = 50;
	snakeRECT.push_back(pieceRECT);

	appleRECT.x = 0;
	appleRECT.y = 50;
	appleRECT.w = 50;
	appleRECT.h = 50;
}

Snake::Snake(Snake &obj) {
	*this = obj;
}

Snake::~Snake() {

}

bool Snake::moveSnake() {

	bool moveLastPiece = true;
	
	if (snakeRECT.size() != snakeSize) {
		moveLastPiece = false;
		pieceRECT.x = snakeRECT[snakeRECT.size() - 1].x;
		pieceRECT.y = snakeRECT[snakeRECT.size() - 1].y;
		pieceRECT.w = snakeRECT[snakeRECT.size() - 1].w;
		pieceRECT.h = snakeRECT[snakeRECT.size() - 1].h;
	}

	for (int i = snakeRECT.size() - 1; i > 0; i--) {
		snakeRECT[i].x = snakeRECT[i - 1].x;
		snakeRECT[i].y = snakeRECT[i - 1].y;
		snakeRECT[i].w = snakeRECT[i - 1].w;
		snakeRECT[i].h = snakeRECT[i - 1].h;
	}

	switch (direction)
	{
		case 'U':
		{
			if (snakeRECT[0].y <= 50)
				return (false);
			snakeRECT[0].y -= 50;
			break ;
		}
		case 'D':
		{
			if (snakeRECT[0].y >= SCREEN_HEIGHT - 100)
				return (false);
			snakeRECT[0].y += 50;
			break ;
		}
		case 'L':
		{
			if (snakeRECT[0].x <= 50)
				return (false);
			snakeRECT[0].x -= 50;
			break ;
		}
		case 'R':
		{
			if (snakeRECT[0].x >= SCREEN_WIDTH - 100)
				return (false);
			snakeRECT[0].x += 50;
			break ;
		}
	}

	if (!moveLastPiece)
		snakeRECT.push_back(pieceRECT);
	return (true);
}

void	Snake::generateApple() {
	bool noCollision = false;

	while (!noCollision) 
	{
		appleRECT.x = (rand() % (SCREEN_WIDTH / 100 - 1) + 1) * 100;
		appleRECT.y = (rand() % (SCREEN_HEIGHT / 100 - 1) + 1) * 100;
		noCollision = true;
		for (int i = 0; i < snakeRECT.size(); i++)
			if (snakeRECT[i].x == appleRECT.x && snakeRECT[i].y == appleRECT.y)
				noCollision = false;
	}
	std::cout << "APPLE x = " << appleRECT.x << " y = " << appleRECT.y << std::endl;
}

bool	Snake::checkCollision() {

	if (snakeRECT[0].x == appleRECT.x && snakeRECT[0].y == appleRECT.y)
	{
		appleRECT.x = -1000;
		appleRECT.y = -1000;
		snakeSize++;
		std::cout << "snakeSize = " << snakeSize << std::endl;
	}
	for (int i = 1; i < snakeRECT.size(); i++)
		if (snakeRECT[0].x == snakeRECT[i].x && snakeRECT[0].y == snakeRECT[i].y)
			return (false);
	return (true);
}
