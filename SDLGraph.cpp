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
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window); 
	SDL_Quit();
}

void	SDLGraph::init() {

	pieceRECT.x = 0;
	pieceRECT.y = 0;
	pieceRECT.w = 110;
	pieceRECT.h = 110;
	snakeRECT.push_back(pieceRECT);

	appleRECT.x = 0;
	appleRECT.y = 50;
	appleRECT.w = 50;
	appleRECT.h = 50;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	window = SDL_CreateWindow("SDLwindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if ( !gRenderer )
		close("SDL_CreateRenderer Error");

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
		close("SDL_image could not initialize! SDL_image Error");

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );

	snake = IMG_LoadTexture(gRenderer, "resources/square.png");
	apple = IMG_LoadTexture(gRenderer, "resources/circle.png");
	if (!snake || !apple)
		close("snake or apple image could not load");
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
	// std::cout << "The " 
	// 			<<  SDL_GetKeyName(event.key.keysym.sym)
	// 			<< " key was pressed!\n";
	// std::cout << "x = " << snakeRECT[0].x << " y = " << snakeRECT[0].y << std::endl;
}

void	SDLGraph::moveSnake() {
	bool moveLastPiece = true;
	
	if (snakeRECT.size() != snakeSize) {
		moveLastPiece = false;
		pieceRECT = snakeRECT[snakeRECT.size() - 1];
	}

	for (int i = snakeRECT.size() - 1; i > 0; i--)
		snakeRECT[i] = snakeRECT[i - 1];

	switch (direction)
	{
		case 'U':
		{
			if (snakeRECT[0].y < 50)
				close("snake outside the box");
			snakeRECT[0].y -= 50;
			break ;
		}
		case 'D':
		{
			if (snakeRECT[0].y >= SCREEN_HEIGHT - 110)
				close("snake outside the box");
			snakeRECT[0].y += 50;
			break ;
		}
		case 'L':
		{
			if (snakeRECT[0].x < 50)
				close("snake outside the box");
			snakeRECT[0].x -= 50;
			break ;
		}
		case 'R':
		{
			if (snakeRECT[0].x >= SCREEN_WIDTH - 110)
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
			if (snakeRECT[i].x == appleRECT.x || snakeRECT[i].y == appleRECT.y)
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

void	SDLGraph::draw() {

	SDL_SetRenderDrawColor( gRenderer, 144, 193, 171, 255 );
	SDL_RenderClear(gRenderer);

	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(gRenderer, 20, 20, 20, SCREEN_HEIGHT - 20);
	SDL_RenderDrawLine(gRenderer, 20, 20, SCREEN_WIDTH - 20, 20);
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH - 20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20);
	SDL_RenderDrawLine(gRenderer, 20, SCREEN_HEIGHT - 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20);
	
	for (int i = 0; i < snakeRECT.size(); i++) {
		SDL_RenderCopy(gRenderer, snake, NULL, &snakeRECT[i]);
	}
	SDL_RenderCopy(gRenderer, apple, NULL, &appleRECT);
	SDL_RenderPresent(gRenderer);
}

void	SDLGraph::mainCycle() {
	int i = 0;

	generateApple();
	while (!quit)
	{
		if (i % 15 == 0)
			moveSnake();
		if (i % 500 == 0 || appleRECT.x == -1000)
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
		checkCollision();
		draw();
		i++;
	}
}
