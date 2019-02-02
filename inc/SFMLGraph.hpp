#pragma once

#include "IGraph.hpp"
#include <SFML/Graphics.hpp>

typedef struct rect
{
	int		x;
	int		y;
	double	w;
	double	h;
	
} rect;

class SFMLGraph : public IGraph
{
	int						SCREEN_WIDTH;
	int						SCREEN_HEIGHT;

	sf::Texture 			texture1;
	sf::Texture 			texture2;
	sf::Texture 			texture3;
	std::vector<rect>		snakeRECT;

	sf::Sprite				squareSprite;
	sf::Sprite				appleSprite;
	sf::Sprite				background;
	char					direction;
	int						snakeSize;
	sf::RenderWindow		*window;

	sf::Event				event;

	rect					appleRECT;
	rect					pieceRECT;  

public:

	bool			quit;

	SFMLGraph();
	SFMLGraph(SFMLGraph &obj);
	SFMLGraph(int width, int height);

	virtual int		close(std::string msg);
	// virtual void	mainCycle();
	virtual void	init();
	virtual void	draw();
	virtual void	move();
	virtual void	moveSnake();
	virtual void	generateApple();
	virtual void	checkCollision();
	virtual bool	windIsOpen();
	virtual void	handleEvent();
};
