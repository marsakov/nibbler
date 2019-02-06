#pragma once

#include "IGraph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SDLGraph : public IGraph
{
	SDL_Window				*window;
	SDL_Renderer			*gRenderer;
	SDL_Texture 			*snakeTexture;
	SDL_Texture 			*appleTexture;
	SDL_Rect				msgRECT;
	SDL_Rect				rectForSDL;
	SDL_Event				event;
	TTF_Font				*textFont;
	SDL_Texture				*msg;


public:

	bool			quit;

	SDLGraph();
	SDLGraph(SDLGraph &obj);
	SDLGraph(Snake *s);
	virtual ~SDLGraph();


	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw();
	virtual void			drawMenu();
	virtual eKeyType		getKey();
	virtual bool			windIsOpen();
	virtual eKeyType		handleEvent();

	SDL_Rect				toSDLRect(rect r);
	
	void					renderText(const char *text, int x, int y);
};
