#include "SFMLGraph.hpp"

SFMLGraph::SFMLGraph() {
	
	quit = false;
	direction = 'R';
	snakeSize = 1;

	SCREEN_WIDTH = 1000;
	SCREEN_HEIGHT = 900;
	init();
}

SFMLGraph::SFMLGraph(int width, int height) {
	
	quit = false;
	direction = 'R';
	snakeSize = 1;

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	init();
}

// SFMLGraph::SFMLGraph(SFMLGraph &obj) {
// 	*this = obj;
// }

SFMLGraph::~SFMLGraph() {

}

void	SFMLGraph::init() {
	
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nibbler");

	sf::Texture texture1;
    texture1.loadFromFile("resources/square.png");
    appleSprite.setTexture(texture1);
	appleSprite.setPosition(20, 20);

	sf::Texture texture2;
    texture2.loadFromFile("resources/apple.png");

    squareSprite = new sf::Sprite(texture2);
	squareSprite->setPosition(150, 150);
}

// int		SFMLGraph::close(std::string msg) {
// 	std::cout << msg << std::endl;
// 	this->~SFMLGraph();
// 	exit(1);
// 	return (0);
// }

// void	SFMLGraph::move() {
// 	switch( event.key.keysym.sym )
// 	{
// 		case SDLK_UP:		(direction == 'D' && snakeSize > 1) ? close("boom") : direction = 'U'; break ;
// 		case SDLK_DOWN:		(direction == 'U' && snakeSize > 1) ? close("boom") : direction = 'D'; break ;
// 		case SDLK_LEFT:		(direction == 'R' && snakeSize > 1) ? close("boom") : direction = 'L'; break ;
// 		case SDLK_RIGHT:	(direction == 'L' && snakeSize > 1) ? close("boom") : direction = 'R'; break ;
// 		case SDLK_ESCAPE:	close("Exit with escape");
// 	}
// }

// void	SFMLGraph::moveSnake() {
// 	bool moveLastPiece = true;
	
// 	if (snakeRECT.size() != snakeSize) {
// 		moveLastPiece = false;
// 		pieceRECT = snakeRECT[snakeRECT.size() - 1];
// 	}

// 	for (int i = snakeRECT.size() - 1; i > 0; i--)
// 		snakeRECT[i] = snakeRECT[i - 1];

// 	switch (direction)
// 	{
// 		case 'U':
// 		{
// 			if (snakeRECT[0].y <= 50)
// 				close("snake outside the box");
// 			snakeRECT[0].y -= 50;
// 			break ;
// 		}
// 		case 'D':
// 		{
// 			if (snakeRECT[0].y >= SCREEN_HEIGHT - 100)
// 				close("snake outside the box");
// 			snakeRECT[0].y += 50;
// 			break ;
// 		}
// 		case 'L':
// 		{
// 			if (snakeRECT[0].x <= 50)
// 				close("snake outside the box");
// 			snakeRECT[0].x -= 50;
// 			break ;
// 		}
// 		case 'R':
// 		{
// 			if (snakeRECT[0].x >= SCREEN_WIDTH - 100)
// 				close("snake outside the box");
// 			snakeRECT[0].x += 50;
// 			break ;
// 		}
// 	}

// 	if (!moveLastPiece)
// 		snakeRECT.push_back(pieceRECT);
// 	// std::cout << "x = " << snakeRECT[0].x << " y = " << snakeRECT[0].y << std::endl;
// }

// void	SFMLGraph::generateApple() {
// 	bool noCollision = false;

// 	while (!noCollision) 
// 	{
// 		appleRECT.x = (rand() % (SCREEN_WIDTH / 100 - 1) + 1) * 100;
// 		appleRECT.y = (rand() % (SCREEN_HEIGHT / 100 - 1) + 1) * 100;
// 		noCollision = true;
// 		for (int i = 0; i < snakeRECT.size(); i++)
// 			if (snakeRECT[i].x == appleRECT.x && snakeRECT[i].y == appleRECT.y)
// 				noCollision = false;
// 	}
// 	std::cout << "APPLE x = " << appleRECT.x << " y = " << appleRECT.y << std::endl;
// }

// void	SFMLGraph::checkCollision() {

// 	if (snakeRECT[0].x == appleRECT.x && snakeRECT[0].y == appleRECT.y)
// 	{
// 		appleRECT.x = -1000;
// 		appleRECT.y = -1000;
// 		snakeSize++;
// 		std::cout << "snakeSize = " << snakeSize << std::endl;
// 	}
// 	for (int i = 1; i < snakeRECT.size(); i++)
// 		if (snakeRECT[0].x == snakeRECT[i].x && snakeRECT[0].y == snakeRECT[i].y)
// 			close("boom");

// }

void	SFMLGraph::draw() {
  window->clear();
  window->draw(*squareSprite);
  window->draw(appleSprite);
  window->display();

}

void	SFMLGraph::mainCycle() {
	// size_t i = 0;

	// generateApple();
	while (window->isOpen()) {
	// 	if (i % 15 == 0)
	// 		moveSnake();
	// 	if (i % 500 == 0 || appleRECT.x == -1000)
	// 		generateApple();
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		draw();
	// 	// std::cout << "Milliseconds since start time " << SDL_GetTicks() - startTime << std::endl; 
	// 	checkCollision();
	// 	draw();
	// 	i++;
	}
}
