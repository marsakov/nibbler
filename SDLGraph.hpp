#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class SDLGraph
{
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	SDL_Window		*window;
	SDL_Renderer	*gRenderer;
	SDL_Texture		*gTexture;
	SDL_Texture 	*player;
	SDL_Rect		player_RECT;
	SDL_Event		event;

public:

	bool			quit;

	SDLGraph();
	~SDLGraph();

	void	mainCycle();
	void	close(std::string msg);

};