#pragma once

// #include <SFML/Graphics.hpp>
#include "IGraph.hpp"
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>


class OpenGLGraph : public IGraph
{

	int 					ac;
	char					*av[3]; // char const *

	int w;
    int h;


	static GLfloat x;
	static GLfloat y;
	static GLfloat rsize;

	static Snake					*snake1;
	static Snake					*snake2;

	// Step size in x and y directions
	// (number of pixels to move each time)
	GLfloat xstep;
	GLfloat ystep;

	// Keep track of windows changing width and height
	GLfloat windowWidth;
	GLfloat windowHeight;

	// sf::Texture 			texture1;
	// sf::Texture 			texture2;
	// sf::Texture 			texture3;
	// sf::Sprite				squareSprite;
	// sf::Sprite				appleSprite;
	// sf::Sprite				background;
	// sf::RenderWindow		*window;
	// sf::Event				event;
protected:
	bool					multiplayer;
	eKeyType				key;


public:

	bool					quit;

	OpenGLGraph();
	OpenGLGraph(OpenGLGraph &obj);
	OpenGLGraph(Snake *s1, Snake *s2);
	virtual ~OpenGLGraph();


	//void 			RenderScene(void);
	// virtual void 			TimerFunction(int value);
	// virtual void 			SetupRC(void);
	// virtual void 			ChangeSize(int w, int h);




	// virtual void 			init();
	// virtual int				close(std::string msg);

	
	// static  void			draw();
	// virtual void			drawMenu();
	// virtual eKeyType		getKey();
	// virtual bool			windIsOpen();
	// virtual void			handleEvent();


	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	static void 				draw1();
	virtual void			drawMenu(int buttonNum, bool start, int speed);
	virtual bool			windIsOpen();
	virtual void			handleEvent();
	virtual	void			setMultiplayer(bool m);
	virtual void			setKeyDown();
	virtual eKeyType		getKey();
	virtual void			setKey(eKeyType k);

};
