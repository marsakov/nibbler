#pragma once

#include "IGraph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <iostream> 

class SDLGraph : public IGraph
{
	SDL_Window				*window;
	SDL_Renderer			*gRenderer;
	SDL_Texture 			*snake1Texture;
	SDL_Texture 			*snake2Texture;
	SDL_Texture 			*appleTexture;
	SDL_Rect				msgRECT;
	SDL_Rect				rectForSDL;
	SDL_Event				event;
	//TTF_Font				*textFont;
	SDL_Texture				*msg;
	Snake					*snake1;
	Snake					*snake2;

protected:
	bool					multiplayer;
	eKeyType				key;

public:

	bool					quit;

	SDLGraph();
	SDLGraph(SDLGraph &obj);
	SDLGraph(Snake *s1, Snake *s2);
	virtual ~SDLGraph();


	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	virtual void			drawMenu(int buttonNum, bool start, int speed);
	virtual bool			windIsOpen();
	virtual void			handleEvent();
	virtual	void			setMultiplayer(bool m);
	virtual void			setKeyDown();
	virtual eKeyType		getKey();
	virtual void			setKey(eKeyType k);

	SDL_Rect				toSDLRect(rect r);
	
	void					renderText(const char *text, int x, int y, bool selection);
};
