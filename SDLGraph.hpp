#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class SDLGraph
{
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window				*window;
	SDL_Renderer			*gRenderer;
	SDL_Texture 			*snake;
	SDL_Texture 			*apple;
	std::vector<SDL_Rect>	snakeRECT;
	SDL_Rect				appleRECT;
	SDL_Rect				pieceRECT;
	SDL_Event				event;
	char					direction;
	int						snakeSize;

public:

	bool			quit;

	SDLGraph();
	SDLGraph(SDLGraph &obj);
	SDLGraph(int width, int height);
	~SDLGraph();

	int		close(std::string msg);
	void	mainCycle();
	void	init();
	void	draw();
	void	move();
	void	moveSnake();
	void	generateApple();
	void	checkCollision();
};
