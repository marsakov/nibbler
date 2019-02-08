#include "../inc/SFMLGraph.hpp"

SFMLGraph::SFMLGraph() {
	
	snake1->direction = 'R';
	snake1->size = 1;
	snake1->screenWidth = 1000;
	snake1->screenHeiht = 900;
	init();
}

SFMLGraph::SFMLGraph(Snake *s1, Snake *s2) {
	std::cout << "SFMLGraph" << std::endl;
	snake1 = s1;
	snake2 = s2;
	std::cout << "w = " << snake1->screenWidth << " h = " << snake1->screenHeiht << std::endl;
	init();
}

SFMLGraph::SFMLGraph(SFMLGraph &obj) {
	*this = obj;
}

SFMLGraph::~SFMLGraph() {
	window->close();
}

void		SFMLGraph::init() {
	
	window = new sf::RenderWindow(sf::VideoMode(snake1->screenWidth*2, snake1->screenHeiht*2), "Nibbler", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

    texture1.loadFromFile("resources/apple1.png");
    texture2.loadFromFile("resources/square1.png");
    texture3.loadFromFile("resources/bckgrnd.jpg");
	font.loadFromFile("resources/SEASRN.ttf");
	text.setStyle(sf::Text::Bold);
	text.setFont(font);
	text.setCharacterSize(42);
	text.setFillColor(sf::Color::White);

    line1 = new sf::RectangleShape(sf::Vector2f(snake1->screenWidth * 2 - 200, 2));
	line2 = new sf::RectangleShape(sf::Vector2f(snake1->screenWidth * 2 - 200, 2));
	line3 = new sf::RectangleShape(sf::Vector2f(2, snake1->screenHeiht * 2 - 200));
	line4 = new sf::RectangleShape(sf::Vector2f(2, snake1->screenHeiht * 2 - 200));

	line1->setPosition(100, 100);
	line2->setPosition(100, snake1->screenHeiht * 2 - 100);
	line3->setPosition(100, 100);
	line4->setPosition(snake1->screenWidth * 2 - 100, 100);

    appleSprite.setTexture(texture1);
    squareSprite.setTexture(texture2);
    background.setTexture(texture3);

	appleSprite.setScale(0.3, 0.3);
	squareSprite.setScale(0.3, 0.3);
	float scale = std::max(snake1->screenWidth, snake1->screenHeiht) / 100 * 0.1 + 0.25;
	std::cout << scale << std::endl;
	background.setScale(scale, scale);

}

int			SFMLGraph::close(std::string msg) {
	std::cout << msg << std::endl;
	this->~SFMLGraph();
	exit(1);
	return (0);
}

eKeyType	SFMLGraph::getKey() {
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

void		SFMLGraph::renderText(std::string textString, int x, int y, bool selection) {

	text.setString(textString);
	text.setPosition(x, y);
	if (selection)
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	else
		text.setStyle(sf::Text::Bold);
	window->draw(text);
}

void		SFMLGraph::drawMenu(int buttonNum, bool start, int speed) {

	window->clear();
	window->draw(background);

	window->draw(*line1);
	window->draw(*line2);
	window->draw(*line3);
	window->draw(*line4);

	if (start)
		renderText("CONTINUE", snake1->screenWidth - 100, snake1->screenHeiht - 200, (buttonNum == 1) ? true : false);
	renderText("NEW GAME", snake1->screenWidth - 100, snake1->screenHeiht - 100, (buttonNum == 2) ? true : false);
	renderText(std::string("MULTIPLAYER  [") + (multiplayer ? "ON]" : "OFF]"), snake1->screenWidth - 100, snake1->screenHeiht, (buttonNum == 3) ? true : false);
	renderText("EXIT", snake1->screenWidth - 100, snake1->screenHeiht + 100, (buttonNum == 4) ? true : false);
	renderText(("SPEED  " + std::to_string(speed)).c_str(), snake1->screenWidth - 100, snake1->screenHeiht - 600, false);


	window->draw(text);

	window->display();
}

void		SFMLGraph::draw(rect appleRect) {
	window->clear();
	window->draw(background);

	window->draw(*line1);
	window->draw(*line2);
	window->draw(*line3);
	window->draw(*line4);

	text.setStyle(sf::Text::Bold);
	text.setString("SCORE " + std::to_string(snake1->size));
	text.setPosition(100, 20);
	window->draw(text);

	appleSprite.setPosition(appleRect.x * 2, appleRect.y * 2);
	window->draw(appleSprite);
	for (int i = 0; i < snake1->snakeRect.size(); i++) {
		squareSprite.setPosition(snake1->snakeRect[i].x * 2, snake1->snakeRect[i].y * 2);
		window->draw(squareSprite);
	}

	if (multiplayer) {
		for (int i = 0; i < snake2->snakeRect.size(); i++) {
			squareSprite.setPosition(snake2->snakeRect[i].x * 2, snake2->snakeRect[i].y * 2);
			window->draw(squareSprite);
		}
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

extern "C" IGraph *createGraph(Snake *s1, Snake *s2) {
	return (new SFMLGraph(s1, s2));
}

extern "C"	void destroyGraph(IGraph *graph) {
	delete graph;
}
