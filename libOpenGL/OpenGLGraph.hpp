#pragma once

#include "../inc/IGraph.hpp"
#include <SDL2/SDL.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <iostream> 

class SDLGraph : public IGraph
{
	SDL_Window				*window;
	SDL_Event				event;
	Snake					*snake1;
	Snake					*snake2;
	float xrf, yrf, zrf;
	double x,y,z;
	double k;
	double x1, y1;

protected:
	bool					multiplayer;
	eKeyType				key;

public:

	bool					quit;

	SDLGraph();
	SDLGraph(SDLGraph &obj);
	SDLGraph(Snake *s1, Snake *s2);
	virtual ~SDLGraph();


	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	void  					drawSnake3D();

	void 					drawApple3DSphera(rect appleRect);
	void 					drawApple3DCube(rect appleRect);
	void					drawCubeFrame(rect snakeRect);
	void					drawCube(rect snakeRect, rect snakeColor);

	virtual void			drawMenu(int buttonNum, bool start, int speed);
	virtual bool			windIsOpen();
	virtual void			handleEvent();
	virtual	void			setMultiplayer(bool m);
	virtual void			setKeyDown();
	void 					setKeyDownRotate();
	virtual eKeyType		getKey();
	virtual void			setKey(eKeyType k);
	void 					drawSphere(double r, int lats, int longs, rect appleRect);
	void 					drawFrame();
	virtual void			drawGameOver(int winner);



	SDL_Rect				toSDLRect(rect r);
	
	void					renderText(const char *text, int x, int y, bool selection);
};
