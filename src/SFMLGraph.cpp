#include "../inc/SFMLGraph.hpp"

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

SFMLGraph::SFMLGraph(SFMLGraph &obj) {
	*this = obj;
}


void	SFMLGraph::init() {
	
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nibbler", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

    texture1.loadFromFile("resources/apple.png");
    texture2.loadFromFile("resources/square.png");
    texture3.loadFromFile("resources/bckgrnd.jpg");

    appleSprite.setTexture(texture1);
    squareSprite.setTexture(texture2);
    background.setTexture(texture3);

	pieceRECT.x = 50;
	pieceRECT.y = 50;
	pieceRECT.w = 0.1;
	pieceRECT.h = 0.1;

    snakeRECT.push_back(pieceRECT);
	appleSprite.setScale(0.1, 0.1);
	squareSprite.setScale(0.1, 0.1);
	background.setScale(5, 5);

}

int		SFMLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SFMLGraph();
	exit(1);
	return (0);
}

void	SFMLGraph::move() {
	switch( event.key.code )
	{
		case sf::Keyboard::Up:			(direction == 'D' && snakeSize > 1) ? close("boom") : direction = 'U'; break ;
		case sf::Keyboard::Down:		(direction == 'U' && snakeSize > 1) ? close("boom") : direction = 'D'; break ;
		case sf::Keyboard::Left:		(direction == 'R' && snakeSize > 1) ? close("boom") : direction = 'L'; break ;
		case sf::Keyboard::Right:		(direction == 'L' && snakeSize > 1) ? close("boom") : direction = 'R'; break ;
		case sf::Keyboard::Escape:		close("Exit with escape");
		default : break ; 
	}
}

void	SFMLGraph::moveSnake() {
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

void	SFMLGraph::generateApple() {
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

void	SFMLGraph::checkCollision() {

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

void	SFMLGraph::draw() {
	window->clear();
	window->draw(background);
	appleSprite.setPosition(appleRECT.x, appleRECT.y);
	window->draw(appleSprite);
	for (int i = 0; i < snakeRECT.size(); i++) {
		squareSprite.setPosition(snakeRECT[i].x, snakeRECT[i].y);
		window->draw(squareSprite);
	}

	
	window->display();
}

void	SFMLGraph::handleEvent() {
	while (window->pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window->close(); break;
			case sf::Event::KeyPressed:
				move(); break;
			default : break ; 
		}
	}
}

bool	SFMLGraph::windIsOpen() {
	return (window->isOpen());
}


// void	SFMLGraph::mainCycle() {
// 	size_t i = 0;

// 	generateApple();
// 	while (windIsOpen()) {
// 		if (i % 15 == 0)
// 			moveSnake();
// 		if (i % 750 == 0 || appleRECT.x == -1000)
// 			generateApple();
// 		handleEvent();
// 		checkCollision();
// 		draw();
// 		i++;
// 	}
// }

extern "C" IGraph *createGraph(int x, int y) {
	return (new SFMLGraph(x, y));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
