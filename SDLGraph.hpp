#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>

class SDLGraph
{
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window				*window;
	SDL_Renderer			*gRenderer;
	SDL_Texture 			*snake;
	SDL_Texture 			*apple;
	SDL_Rect				msgRECT;
	std::vector<SDL_Rect>	snakeRECT;
	SDL_Rect				appleRECT;
	SDL_Rect				pieceRECT;
	SDL_Event				event;
	TTF_Font				*textFont;
	SDL_Surface				*surfaceMsg;
	SDL_Texture				*msg;
	char					direction;
	int						snakeSize;
	Uint32					startTime;

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
	void	renderText(const char *text);
};
