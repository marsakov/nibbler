#pragma once

#include "IGraph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SDLGraph : public IGraph
{
	// int						SCREEN_WIDTH;
	// int						SCREEN_HEIGHT;

	SDL_Window				*window;
	SDL_Renderer			*gRenderer;
	SDL_Texture 			*snakeTexture;
	SDL_Texture 			*appleTexture;
	SDL_Rect				msgRECT;
	// std::vector<SDL_Rect>	snakeRECT;
	// SDL_Rect				appleRECT;
	// SDL_Rect				pieceRECT;
	SDL_Rect				rectForSDL;
	SDL_Event				event;
	TTF_Font				*textFont;
	SDL_Surface				*surfaceMsg;
	SDL_Texture				*msg;
	// char					direction;
	// int						snakeSize;

public:

	bool			quit;

	SDLGraph();
	SDLGraph(SDLGraph &obj);
	SDLGraph(int width, int height, Snake *s);

	virtual int		close(std::string msg);
	virtual void	init();
	virtual void	draw();
	virtual int		move();
	virtual bool	windIsOpen();
	virtual int		handleEvent();

	SDL_Rect		toSDLRect(rect r);
	
	void			renderText(const char *text);
};
