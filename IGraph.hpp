
#pragma once

class IGraph
{
protected:
	int						SCREEN_WIDTH;
	int						SCREEN_HEIGHT;

	char					direction;
	int						snakeSize;

public:

	bool					quit;


	virtual ~SDLGraph() = 0;

	virtual int		close(std::string msg) = 0;
	virtual void	mainCycle() = 0;
	virtual void	init() = 0;
	virtual void	draw() = 0;
	virtual void	move() = 0;
	virtual void	moveSnake() = 0;
	virtual void	generateApple() = 0;
	virtual void	checkCollision() = 0;
	virtual void	renderText(const char *text) = 0;
	
};
