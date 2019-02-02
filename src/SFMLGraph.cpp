#include "../inc/SFMLGraph.hpp"

SFMLGraph::SFMLGraph() {
	
	snake->direction = 'R';
	snake->snakeSize = 1;

	snake->SCREEN_WIDTH = 1000;
	snake->SCREEN_HEIGHT = 900;
	init();
}

SFMLGraph::SFMLGraph(int width, int height, Snake *s) {
	
	snake = s;
	snake->direction = 'R';
	snake->snakeSize = 1;

	snake->SCREEN_WIDTH = width;
	snake->SCREEN_HEIGHT = height;
	init();
}

SFMLGraph::SFMLGraph(SFMLGraph &obj) {
	*this = obj;
}


void	SFMLGraph::init() {
	
	window = new sf::RenderWindow(sf::VideoMode(snake->SCREEN_WIDTH, snake->SCREEN_HEIGHT), "Nibbler", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

    texture1.loadFromFile("resources/apple.png");
    texture2.loadFromFile("resources/square.png");
    texture3.loadFromFile("resources/bckgrnd.jpg");

    appleSprite.setTexture(texture1);
    squareSprite.setTexture(texture2);
    background.setTexture(texture3);

	snake->pieceRECT.x = 50;
	snake->pieceRECT.y = 50;
	snake->pieceRECT.w = 0.1;
	snake->pieceRECT.h = 0.1;

    snake->snakeRECT.push_back(snake->pieceRECT);
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

int		SFMLGraph::move() {
	switch( event.key.code )
	{
		case sf::Keyboard::Up:			(snake->direction == 'D' && snake->snakeSize > 1) ? close("boom") : snake->direction = 'U'; break ;
		case sf::Keyboard::Down:		(snake->direction == 'U' && snake->snakeSize > 1) ? close("boom") : snake->direction = 'D'; break ;
		case sf::Keyboard::Left:		(snake->direction == 'R' && snake->snakeSize > 1) ? close("boom") : snake->direction = 'L'; break ;
		case sf::Keyboard::Right:		(snake->direction == 'L' && snake->snakeSize > 1) ? close("boom") : snake->direction = 'R'; break ;
		case sf::Keyboard::Escape:		close("Exit with escape");
		case sf::Keyboard::Num1:		return (1);
		case sf::Keyboard::Num2:		return (2);
		case sf::Keyboard::Num3:		return (3);
		default : break ; 
	}
	return (0);
}

void	SFMLGraph::draw() {
	window->clear();
	window->draw(background);
	appleSprite.setPosition(snake->appleRECT.x, snake->appleRECT.y);
	window->draw(appleSprite);
	for (int i = 0; i < snake->snakeRECT.size(); i++) {
		squareSprite.setPosition(snake->snakeRECT[i].x, snake->snakeRECT[i].y);
		window->draw(squareSprite);
	}

	
	window->display();
}

int		SFMLGraph::handleEvent() {
	int num;

	while (window->pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window->close(); break;
			case sf::Event::KeyPressed:
			{
				if ( (num = move()) != 0)
					return (num);
				break;
			}
			default : break ; 
		}
	}
	return (0);
}

bool	SFMLGraph::windIsOpen() {
	return (window->isOpen());
}

extern "C" IGraph *createGraph(int x, int y, Snake *s) {
	return (new SFMLGraph(x, y, s));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
