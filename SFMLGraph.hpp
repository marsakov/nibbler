#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class SFMLGraph
{
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	sf::Sprite				*squareSprite;
	sf::Sprite				appleSprite;
	char					direction;
	int						snakeSize;
	sf::RenderWindow		*window;

public:

	bool			quit;

	SFMLGraph();
	SFMLGraph(SFMLGraph &obj);
	SFMLGraph(int width, int height);
	~SFMLGraph();

	int		close(std::string msg);
	void	mainCycle();
	void	init();
	void	draw();
	void	move();
	void	moveSnake();
	void	generateApple();
	void	checkCollision();
};
