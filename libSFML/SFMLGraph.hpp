#pragma once

#include "../inc/IGraph.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

class SFMLGraph : public IGraph
{
	sf::Texture 			texture1;
	sf::Texture 			texture2;
	sf::Texture 			texture3;
	sf::Texture 			texture4;
	sf::Texture 			texture5;
	sf::Texture 			texture6;
	sf::Texture 			texture7;
	sf::Font				font;
	sf::Text				text;
	sf::RectangleShape		*line1;
	sf::RectangleShape		*line2;
	sf::RectangleShape		*line3;
	sf::RectangleShape		*line4;
	sf::Sprite				squareSprite;
	sf::Sprite				squareSprite2;
	sf::Sprite				appleSprite;
	sf::Sprite				boomSprite;
	sf::Sprite				background;
	sf::Sprite				headSprite;
	sf::Sprite				headSprite2;
	sf::RenderWindow		*window;
	sf::Event				event;
	Snake					*snake1;
	Snake					*snake2;

protected:
	bool					network;
	bool					multiplayer;
	eKeyType				key;


public:

	bool					quit;

	SFMLGraph();
	SFMLGraph(SFMLGraph &obj);
	SFMLGraph(Snake *s1, Snake *s2);
	virtual ~SFMLGraph();

	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	virtual void			drawMenu(int buttonNum, bool start, int speed);
	virtual bool			windIsOpen();
	virtual void			handleEvent();
	virtual	void			setMultiplayer(bool m);
	virtual	void			setNetwork(bool m);
	virtual void			setKeyDown();
	virtual eKeyType		getKey();
	virtual void			setKey(eKeyType k);
	virtual void			drawGameOver(int winner, rect boomRect);
	

	void					renderText(std::string text, int x, int y, bool selection);

};
