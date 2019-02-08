#include "../inc/SDLGraph.hpp"

SDLGraph::SDLGraph() {

	quit = false;
	snake1->direction = 'R';
	snake1->size = 1;
	init();
}

SDLGraph::SDLGraph(Snake *s1, Snake *s2) {
	std::cout << "SDLGraph" << std::endl;
	snake1 = s1;
	snake2 = s2;
	std::cout << "w = " << snake1->screenWidth << " h = " << snake1->screenHeiht << std::endl;
	quit = false;
	init();
}

SDLGraph::SDLGraph(SDLGraph &obj) {
	*this = obj;
}

SDLGraph::~SDLGraph() {
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

void		SDLGraph::init() {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	
	window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, snake1->screenWidth, snake1->screenHeiht, SDL_WINDOW_OPENGL);
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
		close("Snake1 or appleTexture image could not load");

	textFont = TTF_OpenFont("resources/SEASRN.ttf", 24);
	if (!textFont)
	{
		std::cout << SDL_GetError() << std::endl;
		close("Unable to render text surface! SDL_ttf Error");
	}
}

int			SDLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SDLGraph();
	exit(1);
	return (0);
}

eKeyType	SDLGraph::getKey() {
	switch( event.key.keysym.sym )
	{
		case SDLK_UP:		return (up);
		case SDLK_DOWN:		return (down);
		case SDLK_LEFT:		return (left);
		case SDLK_RIGHT:	return (right);
		case SDLK_ESCAPE:	return (escape);
		case SDLK_RETURN:	return (enter);
		case SDLK_1:		return (num1);
		case SDLK_2:		return (num2);
		case SDLK_3:		return (num3);
	}
	return (none);
}

void		SDLGraph::renderText(const char *text, int x, int y, bool selection) {

    SDL_Surface *surface;
    SDL_Texture *texture;

	SDL_Color color = { 0, 0, 0, 255 };
    surface = TTF_RenderText_Solid(textFont, text, color);
    msgRECT.x = x;
	msgRECT.y = y;
	msgRECT.w = surface->w;
	msgRECT.h = surface->h;
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    if (selection) {
		SDL_Rect outlineRect = { x, y, surface->w, surface->h };
		SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect( gRenderer, &outlineRect );
	}

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

void		SDLGraph::drawMenu(int buttonNum, bool start, int speed) {

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	if (start)
		renderText("CONTINUE", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 100, (buttonNum == 1) ? true : false);
	renderText("NEW GAME", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 50, (buttonNum == 2) ? true : false);
	renderText((std::string("MULTIPLAYER  [") + (multiplayer ? "ON]" : "OFF]")).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2, (buttonNum == 3) ? true : false);
	renderText("EXIT", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 + 50, (buttonNum == 4) ? true : false);
	renderText(("SPEED  " + std::to_string(speed)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 300, false);

	SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, 50, snake1->screenWidth - 50, 50);
	SDL_RenderDrawLine(gRenderer, snake1->screenWidth - 50, 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, snake1->screenHeiht - 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);

	SDL_RenderPresent(gRenderer);
}

void		SDLGraph::draw(rect appleRect) {

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, 50, snake1->screenWidth - 50, 50);
	SDL_RenderDrawLine(gRenderer, snake1->screenWidth - 50, 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, snake1->screenHeiht - 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
	
	for (int i = 0; i < snake1->snakeRect.size(); i++) {
		rectForSDL = toSDLRect(snake1->snakeRect[i]);
		SDL_RenderCopy(gRenderer, snakeTexture, NULL, &rectForSDL);
	}

	if (multiplayer) {
		for (int i = 0; i < snake2->snakeRect.size(); i++) {
			rectForSDL = toSDLRect(snake2->snakeRect[i]);
			SDL_RenderCopy(gRenderer, snakeTexture, NULL, &rectForSDL);
		}
		renderText(("SCORE = " + std::to_string(snake1->size)).c_str(), snake1->screenWidth - 250, 10, false);
	}

	rectForSDL = toSDLRect(appleRect);
	SDL_RenderCopy(gRenderer, appleTexture, NULL, &rectForSDL);

	renderText(("SCORE = " + std::to_string(snake1->size)).c_str(), 50, 10, false);

	SDL_RenderPresent(gRenderer);
}

eKeyType	SDLGraph::handleEvent() {
	eKeyType num = none;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: {
				if ( (num = getKey()) != none)
					return (num);
				break ;
			}
			case SDL_QUIT:
				close("exit");
		}
	}
	return (none);
}

bool		SDLGraph::windIsOpen() {
	return (!quit);
}

extern "C" IGraph *createGraph(Snake *s1, Snake *s2) {
	return (new SDLGraph(s1, s2));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
