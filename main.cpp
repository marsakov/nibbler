#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLGraph.hpp"

int main(int argc, char *argv[])
{
	SDLGraph sdl;
	while(!sdl.quit)
	{
		sdl.mainCycle();
	}
	return (0);
	sdl.~SDLGraph();
}