#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

	SDL_Renderer	*gRenderer = NULL;

int main(int argc, char *argv[])
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 960;

	SDL_Window		*window = NULL;
	SDL_Event		event;
	SDL_Texture		*gTexture = NULL;
	SDL_Texture 	*player;

	SDL_Rect player_RECT;
		player_RECT.x = 150;
		player_RECT.y = 150;
		player_RECT.w = 100;
		player_RECT.h = 100;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	window = SDL_CreateWindow("SDLwindow", 600, 300, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if ( !gRenderer ) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return (1);
	}

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		std::cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << std::endl;

	// SDL_SetRenderDrawColor( gRenderer, 33, 132, 87, 255 );
	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );

	player =  IMG_LoadTexture(gRenderer, "resources/square.png");
	if (!player)
		std::cout << "player image could not load" << std::endl;

	while (1) 
	{
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
				{
					switch( event.key.keysym.sym )
					{
						case SDLK_UP: player_RECT.y -= 50; break;
						case SDLK_DOWN: player_RECT.y += 50; break;
						case SDLK_LEFT: player_RECT.x -= 50; break;
						case SDLK_RIGHT: player_RECT.x += 50; break;
					}
					std::cout << "The " 
							<<  SDL_GetKeyName(event.key.keysym.sym)
							<< " key was pressed!\n";
					break;
				}
				case SDL_QUIT:
					exit(0);
			}
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, player, NULL, &player_RECT);
			SDL_RenderPresent(gRenderer);
		}
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window); 
	SDL_Quit();
	
	return (0);
}