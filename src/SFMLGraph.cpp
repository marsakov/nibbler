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
	std::cout << "w = " << snake->SCREEN_WIDTH << " h = " << snake->SCREEN_HEIGHT << std::endl;
	init();
}

SFMLGraph::SFMLGraph(SFMLGraph &obj) {
	*this = obj;
}

SFMLGraph::~SFMLGraph() {
	window->close();
}

void	SFMLGraph::init() {
	
	window = new sf::RenderWindow(sf::VideoMode(snake->SCREEN_WIDTH*2, snake->SCREEN_HEIGHT*2), "Nibbler", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

    texture1.loadFromFile("resources/apple.png");
    texture2.loadFromFile("resources/square.png");
    texture3.loadFromFile("resources/bckgrnd.jpg");

    appleSprite.setTexture(texture1);
    squareSprite.setTexture(texture2);
    background.setTexture(texture3);

	appleSprite.setScale(0.3, 0.3);
	squareSprite.setScale(0.3, 0.3);
	background.setScale(10, 10);

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
		case sf::Keyboard::Up:			(snake->direction != 'D') ? snake->direction = 'U' : 0; break ;
		case sf::Keyboard::Down:		(snake->direction != 'U') ? snake->direction = 'D' : 0; break ;
		case sf::Keyboard::Left:		(snake->direction != 'R') ? snake->direction = 'L' : 0; break ;
		case sf::Keyboard::Right:		(snake->direction != 'L') ? snake->direction = 'R' : 0; break ;
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
	appleSprite.setPosition(snake->appleRECT.x * 2, snake->appleRECT.y * 2);
	window->draw(appleSprite);
	for (int i = 0; i < snake->snakeRECT.size(); i++) {
		squareSprite.setPosition(snake->snakeRECT[i].x * 2, snake->snakeRECT[i].y * 2);
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
