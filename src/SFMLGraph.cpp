#include "../inc/SFMLGraph.hpp"

SFMLGraph::SFMLGraph() {
	
	snake->direction = 'R';
	snake->snakeSize = 1;

	snake->SCREEN_WIDTH = 1000;
	snake->SCREEN_HEIGHT = 900;
	init();
}

SFMLGraph::SFMLGraph(Snake *s) {
	std::cout << "SFMLGraph" << std::endl;
	
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

    texture1.loadFromFile("resources/apple1.png");
    texture2.loadFromFile("resources/square1.png");
    texture3.loadFromFile("resources/bckgrnd.jpg");
	font.loadFromFile("resources/SEASRN.ttf");
	text.setStyle(sf::Text::Bold);
	text.setFont(font);
	text.setCharacterSize(42);
	text.setFillColor(sf::Color::White);

    line1 = new sf::RectangleShape(sf::Vector2f(snake->SCREEN_WIDTH * 2 - 200, 2));
	line2 = new sf::RectangleShape(sf::Vector2f(snake->SCREEN_WIDTH * 2 - 200, 2));
	line3 = new sf::RectangleShape(sf::Vector2f(2, snake->SCREEN_HEIGHT * 2 - 200));
	line4 = new sf::RectangleShape(sf::Vector2f(2, snake->SCREEN_HEIGHT * 2 - 200));

	line1->setPosition(100, 100);
	line2->setPosition(100, snake->SCREEN_HEIGHT * 2 - 100);
	line3->setPosition(100, 100);
	line4->setPosition(snake->SCREEN_WIDTH * 2 - 100, 100);

    appleSprite.setTexture(texture1);
    squareSprite.setTexture(texture2);
    background.setTexture(texture3);

	appleSprite.setScale(0.3, 0.3);
	squareSprite.setScale(0.3, 0.3);
	background.setScale(1, 1);

}

int		SFMLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SFMLGraph();
	exit(1);
	return (0);
}

eKeyType		SFMLGraph::getKey() {
	switch( event.key.code )
	{
		case sf::Keyboard::Up:			return (up);
		case sf::Keyboard::Down:		return (down);
		case sf::Keyboard::Left:		return (left);
		case sf::Keyboard::Right:		return (right);
		case sf::Keyboard::Escape:		return (escape);
		case sf::Keyboard::Return:		return (enter);
		case sf::Keyboard::Num1:		return (num1);
		case sf::Keyboard::Num2:		return (num2);
		case sf::Keyboard::Num3:		return (num3);
		default: break;
	}
	return (none);
}

void	SFMLGraph::renderText(std::string textString, int x, int y, bool selection) {

	text.setString(textString);
	text.setPosition(x, y);
	if (selection)
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	else
		text.setStyle(sf::Text::Bold);
	window->draw(text);
}

void	SFMLGraph::drawMenu(int buttonNum, bool start) {

	window->clear();
	window->draw(background);

	window->draw(*line1);
	window->draw(*line2);
	window->draw(*line3);
	window->draw(*line4);

	if (start)
		renderText("CONTINUE", snake->SCREEN_WIDTH - 100, snake->SCREEN_HEIGHT - 200, (buttonNum == 1) ? true : false);
	renderText("NEW GAME", snake->SCREEN_WIDTH - 100, snake->SCREEN_HEIGHT - 100, (buttonNum == 2) ? true : false);
	renderText("SPEED  " + std::to_string(snake->snakeSpeed), snake->SCREEN_WIDTH - 100, snake->SCREEN_HEIGHT, (buttonNum == 3) ? true : false);
	renderText("EXIT", snake->SCREEN_WIDTH - 100, snake->SCREEN_HEIGHT + 100, (buttonNum == 4) ? true : false);

	window->draw(text);

	window->display();
}

void	SFMLGraph::draw() {
	window->clear();
	window->draw(background);

	window->draw(*line1);
	window->draw(*line2);
	window->draw(*line3);
	window->draw(*line4);

	text.setStyle(sf::Text::Bold);
	text.setString("SCORE " + std::to_string(snake->snakeSize));
	text.setPosition(100, 20);
	window->draw(text);

	appleSprite.setPosition(snake->appleRECT.x * 2, snake->appleRECT.y * 2);
	window->draw(appleSprite);
	for (int i = 0; i < snake->snakeRECT.size(); i++) {
		squareSprite.setPosition(snake->snakeRECT[i].x * 2, snake->snakeRECT[i].y * 2);
		window->draw(squareSprite);
	}
	window->display();
}

eKeyType	SFMLGraph::handleEvent() {
	eKeyType num;

	while (window->pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window->close(); break;
			case sf::Event::KeyPressed:
			{
				if ( (num = getKey()) != none)
					return (num);
				break;
			}
			default : break ; 
		}
	}
	return (none);
}

bool	SFMLGraph::windIsOpen() {
	return (window->isOpen());
}

extern "C" IGraph *createGraph(Snake *s) {
	return (new SFMLGraph(s));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
