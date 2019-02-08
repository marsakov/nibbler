#pragma once

#include "IGraph.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>

class SFMLGraph : public IGraph
{
	sf::Texture 			texture1;
	sf::Texture 			texture2;
	sf::Texture 			texture3;
	sf::Font				font;
	sf::Text				text;
	sf::RectangleShape		*line1;
	sf::RectangleShape		*line2;
	sf::RectangleShape		*line3;
	sf::RectangleShape		*line4;
	sf::Sprite				squareSprite;
	sf::Sprite				appleSprite;
	sf::Sprite				background;
	sf::RenderWindow		*window;
	sf::Event				event;
	Snake					*snake1;
	Snake					*snake2;

public:

	bool					quit;
	bool					multiplayer;

	SFMLGraph();
	SFMLGraph(SFMLGraph &obj);
	SFMLGraph(Snake *s1, Snake *s2);
	virtual ~SFMLGraph();

	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	virtual void			drawMenu(int buttonNum, bool start, int speed);
	virtual eKeyType		getKey();
	virtual bool			windIsOpen();
	virtual eKeyType		handleEvent();

	void					renderText(std::string text, int x, int y, bool selection);

};
