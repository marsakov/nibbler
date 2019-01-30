#include "SDLGraph.hpp"

SDLGraph::SDLGraph() {
	
	quit = false;
	direction = 'R';
	snakeSize = 1;

	SCREEN_WIDTH = 1000;
	SCREEN_HEIGHT = 900;
	init();
}

SDLGraph::SDLGraph(int width, int height) {
	
	quit = false;
	direction = 'R';
	snakeSize = 1;

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	init();
}

SDLGraph::SDLGraph(SDLGraph &obj) {
	*this = obj;
}

SDLGraph::~SDLGraph() {
	SDL_DestroyTexture(apple);
	SDL_DestroyTexture(snake);
	SDL_DestroyTexture(msg);
	SDL_FreeSurface(surfaceMsg);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(textFont);
	TTF_Quit();
	SDL_Quit();
	system("leaks a.out");
}

void	SDLGraph::init() {

	pieceRECT.x = 50;
	pieceRECT.y = 50;
	pieceRECT.w = 50;
	pieceRECT.h = 50;
	snakeRECT.push_back(pieceRECT);

	appleRECT.x = 0;
	appleRECT.y = 50;
	appleRECT.w = 50;
	appleRECT.h = 50;

	msgRECT.x = 25;
	msgRECT.y = 10;
	msgRECT.w = 300;
	msgRECT.h = 25;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	
	window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if ( !gRenderer )
		close("SDL_CreateRenderer Error");

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		close("SDL_image could not initialize! SDL_image Error");

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );

	snake = IMG_LoadTexture(gRenderer, "resources/square.png");
	apple = IMG_LoadTexture(gRenderer, "resources/apple.png");
	if (!snake || !apple)
		close("Snake or apple image could not load");

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

void	SDLGraph::move() {
	switch( event.key.keysym.sym )
	{
		case SDLK_UP:		(direction == 'D' && snakeSize > 1) ? close("boom") : direction = 'U'; break ;
		case SDLK_DOWN:		(direction == 'U' && snakeSize > 1) ? close("boom") : direction = 'D'; break ;
		case SDLK_LEFT:		(direction == 'R' && snakeSize > 1) ? close("boom") : direction = 'L'; break ;
		case SDLK_RIGHT:	(direction == 'L' && snakeSize > 1) ? close("boom") : direction = 'R'; break ;
		case SDLK_ESCAPE:	close("Exit with escape");
	}
}

void	SDLGraph::moveSnake() {
	bool moveLastPiece = true;
	
	if (snakeRECT.size() != snakeSize) {
		moveLastPiece = false;
		pieceRECT.x = snakeRECT[snakeRECT.size() - 1].x;
		pieceRECT.y = snakeRECT[snakeRECT.size() - 1].y;
		pieceRECT.w = snakeRECT[snakeRECT.size() - 1].w;
		pieceRECT.h = snakeRECT[snakeRECT.size() - 1].h;
	}

	for (int i = snakeRECT.size() - 1; i > 0; i--) {
		snakeRECT[i].x = snakeRECT[i - 1].x;
		snakeRECT[i].y = snakeRECT[i - 1].y;
		snakeRECT[i].w = snakeRECT[i - 1].w;
		snakeRECT[i].h = snakeRECT[i - 1].h;
	}

	switch (direction)
	{
		case 'U':
		{
			if (snakeRECT[0].y <= 50)
				close("snake outside the box");
			snakeRECT[0].y -= 50;
			break ;
		}
		case 'D':
		{
			if (snakeRECT[0].y >= SCREEN_HEIGHT - 100)
				close("snake outside the box");
			snakeRECT[0].y += 50;
			break ;
		}
		case 'L':
		{
			if (snakeRECT[0].x <= 50)
				close("snake outside the box");
			snakeRECT[0].x -= 50;
			break ;
		}
		case 'R':
		{
			if (snakeRECT[0].x >= SCREEN_WIDTH - 100)
				close("snake outside the box");
			snakeRECT[0].x += 50;
			break ;
		}
	}

	if (!moveLastPiece)
		snakeRECT.push_back(pieceRECT);
	// std::cout << "x = " << snakeRECT[0].x << " y = " << snakeRECT[0].y << std::endl;
}

void	SDLGraph::generateApple() {
	bool noCollision = false;

	while (!noCollision) 
	{
		appleRECT.x = (rand() % (SCREEN_WIDTH / 100 - 1) + 1) * 100;
		appleRECT.y = (rand() % (SCREEN_HEIGHT / 100 - 1) + 1) * 100;
		noCollision = true;
		for (int i = 0; i < snakeRECT.size(); i++)
			if (snakeRECT[i].x == appleRECT.x && snakeRECT[i].y == appleRECT.y)
				noCollision = false;
	}
	std::cout << "APPLE x = " << appleRECT.x << " y = " << appleRECT.y << std::endl;
}

void	SDLGraph::checkCollision() {

	if (snakeRECT[0].x == appleRECT.x && snakeRECT[0].y == appleRECT.y)
	{
		appleRECT.x = -1000;
		appleRECT.y = -1000;
		snakeSize++;
		std::cout << "snakeSize = " << snakeSize << std::endl;
	}
	for (int i = 1; i < snakeRECT.size(); i++)
		if (snakeRECT[0].x == snakeRECT[i].x && snakeRECT[0].y == snakeRECT[i].y)
			close("boom");

}

void	SDLGraph::renderText(const char *text) {

    SDL_Surface *surface;
    SDL_Texture *texture;

	SDL_Color color = { 0, 0, 0, 255 };
    surface = TTF_RenderText_Solid(textFont, text, color);
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    SDL_FreeSurface(surface);
    SDL_RenderCopy(gRenderer, texture, NULL, &msgRECT);
    SDL_DestroyTexture(texture);
}

void	SDLGraph::draw() {

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(gRenderer, 50, 50, 50, SCREEN_HEIGHT - 50);
	SDL_RenderDrawLine(gRenderer, 50, 50, SCREEN_WIDTH - 50, 50);
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH - 50, 50, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);
	SDL_RenderDrawLine(gRenderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);
	
	for (int i = 0; i < snakeRECT.size(); i++) {
		SDL_RenderCopy(gRenderer, snake, NULL, &snakeRECT[i]);
	}
	SDL_RenderCopy(gRenderer, apple, NULL, &appleRECT);

	renderText(("SCORE = " + std::to_string(snakeSize)).c_str());

	SDL_RenderPresent(gRenderer);
}

void	SDLGraph::mainCycle() {
	size_t i = 0;
	startTime = SDL_GetTicks();

	generateApple();
	while (!quit)
	{
		if (i % 15 == 0)
			moveSnake();
		if (i % 750 == 0 || appleRECT.x == -1000)
			generateApple();
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					move(); break ;
				case SDL_QUIT:
					close("exit");
			}
		}
		// std::cout << "Milliseconds since start time " << SDL_GetTicks() - startTime << std::endl; 
		checkCollision();
		draw();
		i++;
	}
}
