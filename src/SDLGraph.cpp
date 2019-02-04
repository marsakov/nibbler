#include "../inc/SDLGraph.hpp"

SDLGraph::SDLGraph() {
	
	quit = false;
	snake->direction = 'R';
	snake->snakeSize = 1;

	snake->SCREEN_WIDTH = 1000;
	snake->SCREEN_HEIGHT = 900;
	init();
}

SDLGraph::SDLGraph(int width, int height, Snake *s) {
	snake = s;
	snake->SCREEN_WIDTH /= 2;
	snake->SCREEN_HEIGHT /= 2;
	std::cout << "w = " << snake->SCREEN_WIDTH << " h = " << snake->SCREEN_HEIGHT << std::endl;
	quit = false;
	init();
}

SDLGraph::SDLGraph(SDLGraph &obj) {
	*this = obj;
}

SDLGraph::~SDLGraph() {
	snake->SCREEN_WIDTH *= 2;
	snake->SCREEN_HEIGHT *= 2;
	if (appleTexture)
		SDL_DestroyTexture(appleTexture);
	if (snakeTexture)
		SDL_DestroyTexture(snakeTexture);
	TTF_CloseFont(textFont);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void	SDLGraph::init() {


	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	
	window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, snake->SCREEN_WIDTH, snake->SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if ( !gRenderer )
		close("SDL_CreateRenderer Error");

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		close("SDL_image could not initialize! SDL_image Error");

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );

	snakeTexture = IMG_LoadTexture(gRenderer, "resources/square.png");
	appleTexture = IMG_LoadTexture(gRenderer, "resources/apple.png");
	if (!snakeTexture || !appleTexture)
		close("Snake or appleTexture image could not load");

	textFont = TTF_OpenFont("resources/SEASRN.ttf", 24);
	if (!textFont)
	{
		std::cout << SDL_GetError() << std::endl;
		close("Unable to render text surface! SDL_ttf Error");
	}
}

int		SDLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SDLGraph();
	exit(1);
	return (0);
}

int		SDLGraph::move() {
	switch( event.key.keysym.sym )
	{
		case SDLK_UP:		(snake->direction != 'D') ? snake->direction = 'U' : 0; break ;
		case SDLK_DOWN:		(snake->direction != 'U') ? snake->direction = 'D' : 0; break ;
		case SDLK_LEFT:		(snake->direction != 'R') ? snake->direction = 'L' : 0; break ;
		case SDLK_RIGHT:	(snake->direction != 'L') ? snake->direction = 'R' : 0; break ;
		case SDLK_ESCAPE:	close("Exit with escape");
		case SDLK_1:		return (1);
		case SDLK_2:		return (2);
		case SDLK_3:		return (3);
	}
	return (0);
}

void	SDLGraph::renderText(const char *text) {

    SDL_Surface *surface;
    SDL_Texture *texture;


	

	SDL_Color color = { 0, 0, 0, 255 };
    surface = TTF_RenderText_Solid(textFont, text, color);
    msgRECT.x = 25;
	msgRECT.y = 10;
	msgRECT.w = surface->w;
	msgRECT.h = surface->h;
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    SDL_FreeSurface(surface);
    SDL_RenderCopy(gRenderer, texture, NULL, &msgRECT);
    SDL_DestroyTexture(texture);
}

SDL_Rect	SDLGraph::toSDLRect(rect r) {
	SDL_Rect sdlR;
	sdlR.x = r.x;
	sdlR.y = r.y;
	sdlR.w = r.w;
	sdlR.h = r.h;
	return (sdlR);
}

void	SDLGraph::draw() {

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake->SCREEN_HEIGHT - 50);
	SDL_RenderDrawLine(gRenderer, 50, 50, snake->SCREEN_WIDTH - 50, 50);
	SDL_RenderDrawLine(gRenderer, snake->SCREEN_WIDTH - 50, 50, snake->SCREEN_WIDTH - 50, snake->SCREEN_HEIGHT - 50);
	SDL_RenderDrawLine(gRenderer, 50, snake->SCREEN_HEIGHT - 50, snake->SCREEN_WIDTH - 50, snake->SCREEN_HEIGHT - 50);
	
	for (int i = 0; i < snake->snakeRECT.size(); i++) {
		rectForSDL = toSDLRect(snake->snakeRECT[i]);
		SDL_RenderCopy(gRenderer, snakeTexture, NULL, &rectForSDL);
	}
	rectForSDL = toSDLRect(snake->appleRECT);
	SDL_RenderCopy(gRenderer, appleTexture, NULL, &rectForSDL);

	renderText(("SCORE = " + std::to_string(snake->snakeSize)).c_str());

	SDL_RenderPresent(gRenderer);
}

int		SDLGraph::handleEvent() {
	int num = 0;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: {
				if ( (num = move()) != 0)
					return (num);
				break ;
			}
			case SDL_QUIT:
				close("exit");
		}
	}
	return (0);
}

bool	SDLGraph::windIsOpen() {
	return (!quit);
}

extern "C" IGraph *createGraph(int x, int y, Snake *s) {
	return (new SDLGraph(x, y, s));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
