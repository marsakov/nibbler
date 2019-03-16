#include "SDLGraph.hpp"

SDLGraph::SDLGraph() {
	key = none;
	quit = false;
	snake1->direction = 'R';
	snake1->size = 1;
	init();
	iter = 1;
}

SDLGraph::SDLGraph(Snake *s1, Snake *s2) {
	snake1 = s1;
	snake2 = s2;
	key = none;
	quit = false;
	init();
	iter = 1;
}

SDLGraph::SDLGraph(SDLGraph &obj) {
	*this = obj;
}

SDLGraph::~SDLGraph() {
	if (appleTexture)
		SDL_DestroyTexture(appleTexture);
	if (snake1Texture)
		SDL_DestroyTexture(snake1Texture);
	if (snake2Texture)
		SDL_DestroyTexture(snake2Texture);
	if (head1Texture)
		SDL_DestroyTexture(head1Texture);
	if (head2Texture)
		SDL_DestroyTexture(head2Texture);
	TTF_CloseFont(textFont);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

eKeyType	SDLGraph::getKey() { return (key); }
void		SDLGraph::setKey(eKeyType k) { key = k; }


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

	snake1Texture = IMG_LoadTexture(gRenderer, "resources/square.png");
	snake2Texture = IMG_LoadTexture(gRenderer, "resources/square1.png");
	head1Texture = IMG_LoadTexture(gRenderer, "resources/squareHead.png");
	head2Texture = IMG_LoadTexture(gRenderer, "resources/squareHead2.png");
	appleTexture = IMG_LoadTexture(gRenderer, "resources/apple.png");
	boomTexture = IMG_LoadTexture(gRenderer, "resources/boom.png");
	if (!snake1Texture || !appleTexture || !snake2Texture)
		close("Snake1 or appleTexture image could not load");

	textFont = TTF_OpenFont("resources/SEASRN.ttf", 24);
	if (!textFont)
		close("Unable to render text surface! SDL_ttf Error");
}

int			SDLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SDLGraph();
	exit(1);
	return (0);
}

void		SDLGraph::setKeyDown() {
	switch( event.key.keysym.sym )
	{
		case SDLK_w:		{ key = w; break; }
		case SDLK_s:		{ key = s; break; }
		case SDLK_a:		{ key = a; break; }
		case SDLK_d:		{ key = d; break; }
		case SDLK_UP:		{ key = up; break; }
		case SDLK_DOWN:		{ key = down; break; }
		case SDLK_LEFT:		{ key = left; break; }
		case SDLK_RIGHT:	{ key = right; break; }
		case SDLK_ESCAPE:	{ key = escape; break; }
		case SDLK_RETURN:	{ key = enter; break; }
		case SDLK_1:		{ key = num1; break; }
		case SDLK_2:		{ key = num2; break; }
		case SDLK_3:		{ key = num3; break; }
		case SDLK_m:		{ key = mute; break; }
		default:			{ key = none; break; }
	}
}

void		SDLGraph::renderText(const char *text, int x, int y, bool selection) {

    SDL_Surface *surface;
    SDL_Texture *texture;

	SDL_Color color = { 0, 0, 0, 255 };
	if (selection) {
		SDL_Color color1 = { 255, 255, 255, 255 };
		color = color1;
	}
    surface = TTF_RenderText_Solid(textFont, text, color);
    msgRECT.x = x;
	msgRECT.y = y;
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

void		SDLGraph::drawMenu(int buttonNum, bool start, bool network, int speed) {

	if (snake1->waiting)
		iter = (iter == 70) ? 1 : iter + 1;

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	if (snake1->muteVar)
		renderText(("MUTE"), 450, 10, false);
	if (start && !network && !snake1->waiting)
		renderText("CONTINUE", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 100, (buttonNum == 1) ? true : false);
	else if (snake1->waiting) {
		renderText("*************************", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 100, false);
		renderText("*", snake1->screenWidth / 2 - 50 + iter * 3, snake1->screenHeiht / 2 - 100, true);
	}
	renderText("NEW GAME", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 50, (buttonNum == 2) ? true : false);
	renderText((std::string("MULTIPLAYER ") + (snake1->multiplayer ? (snake1->network ? "NET" : "LOCAL") : "OFF")).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2, (buttonNum == 3) ? true : false);
	renderText("EXIT", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 + 50, (buttonNum == 4) ? true : false);
	renderText(("SPEED  " + std::to_string(speed)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 300, false);

	SDL_RenderDrawLine(gRenderer, 50, 50, 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, 50, snake1->screenWidth - 50, 50);
	SDL_RenderDrawLine(gRenderer, snake1->screenWidth - 50, 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);
	SDL_RenderDrawLine(gRenderer, 50, snake1->screenHeiht - 50, snake1->screenWidth - 50, snake1->screenHeiht - 50);

	SDL_RenderPresent(gRenderer);
}

void		SDLGraph::drawGameOver(int winner, rect boomRect) {

	boomRect.h = 100;
	boomRect.w = 100;
	boomRect.x -= 25;
	boomRect.y -= 25;
	rectForSDL = toSDLRect(boomRect);
	SDL_RenderCopy(gRenderer, boomTexture, NULL, &rectForSDL);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	renderText("GAME OVER", snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 - 50, false);
	if (snake1->multiplayer) {
		renderText(("Snake1 SCORE " + std::to_string(snake1->size)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2, (winner == 1) ? true : false);
		renderText(("Snake2 SCORE " + std::to_string(snake2->size)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2 + 50, (winner == 2) ? true : false);
	}
	else
		renderText(("Snake1 SCORE " + std::to_string(snake1->size)).c_str(), snake1->screenWidth / 2 - 50, snake1->screenHeiht / 2, true);


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
	
	appleRect.h = 50;
	appleRect.w = 50;
	rectForSDL = toSDLRect(appleRect);
	SDL_RenderCopy(gRenderer, appleTexture, NULL, &rectForSDL);
	if (snake1->muteVar)
		renderText(("MUTE"), 450, 10, false);
	renderText(("SCORE = " + std::to_string(snake1->size)).c_str(), 50, 10, false);
	for (size_t i = 0; i < snake1->snakeRect.size(); i++) { 
		if (i == 0) {
			rectForSDL = toSDLRect(snake1->snakeRect[i]);
			SDL_RenderCopy(gRenderer, head1Texture, NULL, &rectForSDL);
		} else {
			rectForSDL = toSDLRect(snake1->snakeRect[i]);
			SDL_RenderCopy(gRenderer, snake1Texture, NULL, &rectForSDL);
		}
		
	}
	if (snake1->multiplayer) {
		for (size_t i = 0; i < snake2->snakeRect.size(); i++) {
			if (i == 0) {
				rectForSDL = toSDLRect(snake2->snakeRect[i]);
				SDL_RenderCopy(gRenderer, head2Texture, NULL, &rectForSDL);
			} else {
				rectForSDL = toSDLRect(snake2->snakeRect[i]);
				SDL_RenderCopy(gRenderer, snake2Texture, NULL, &rectForSDL);
			}
			
		}
		renderText(("SCORE = " + std::to_string(snake2->size)).c_str(), snake2->screenWidth - 250, 10, false);
	}
	SDL_RenderPresent(gRenderer);
}

void	SDLGraph::handleEvent() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				setKeyDown(); break ;
			case SDL_QUIT:
				close("exitSDLhandleEvent");
		}
	}
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
