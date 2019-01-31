#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

typedef struct rect
{
	int x;
	int y;
	double w;
	double h;
	
} rect;

class SFMLGraph
{
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

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


	//SDL_Rect				appleRECT;
	rect					appleRECT;
	rect					pieceRECT;  
	//snakeRECTx[i]
	// int 					snakeRECTx[];
	// int 					snakeRECTy[];

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
