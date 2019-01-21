#include "SDLGraph.hpp"

SDLGraph::SDLGraph() {
	
	quit = false;

	SCREEN_WIDTH = 1280;
	SCREEN_HEIGHT = 960;

	player_RECT.x = 150;
	player_RECT.y = 150;
	player_RECT.w = 100;
	player_RECT.h = 100;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	window = SDL_CreateWindow("SDLwindow", 600, 300, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if ( !gRenderer )
		close("SDL_CreateRenderer Error");


	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		close("SDL_image could not initialize! SDL_image Error");

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );

	player =  IMG_LoadTexture(gRenderer, "resources/square.png");
	if (!player)
		close("player image could not load");
}


SDLGraph::~SDLGraph() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window); 
	SDL_Quit();
}

void	SDLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SDLGraph();
	exit(1);
}

void	SDLGraph::mainCycle() {

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
				break ;
			}
			case SDL_QUIT:
				close("exit");
		}
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, player, NULL, &player_RECT);
		SDL_RenderPresent(gRenderer);
	}
}
