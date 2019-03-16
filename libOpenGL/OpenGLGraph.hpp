#pragma once

#include "../inc/IGraph.hpp"
#include <SDL2/SDL.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <iostream> 

class OpenGLGraph : public IGraph
{
	SDL_Window				*window;
	SDL_Event				event;
	Snake					*snake1;
	Snake					*snake2;
	float 					xrf, yrf, zrf;
	double 					x,y,z;
	double 					k;
	double 					x1, y1, y2, y3, z1;
	bool					D3;

protected:
	eKeyType				key;

	int iter;
public:

	bool					quit;

	OpenGLGraph();
	OpenGLGraph(OpenGLGraph &obj);
	OpenGLGraph(Snake *s1, Snake *s2);
	virtual ~OpenGLGraph();


	virtual int				close(std::string msg);
	virtual void			init();
	virtual void			draw(rect appleRect);
	void  					drawSnake3D();

	void 					drawApple3DSphera(rect appleRect);
	void 					drawApple3DCube(rect appleRect);
	void					drawCubeFrame(rect snakeRect);
	void					drawCube(rect snakeRect, rect snakeColor, int i);

	virtual void			drawMenu(int buttonNum, bool start, bool network, int speed);
	virtual bool			windIsOpen();
	virtual void			handleEvent();
	virtual void			setKeyDown();
	void 					setKeyDownRotate();
	virtual eKeyType		getKey();
	virtual void			setKey(eKeyType k);
	void 					drawSphere(double r, int lats, int longs, rect appleRect);
	void 					drawFrame2D();
	void 					drawFrame3D();
	void        			drawFrameMenu();
	virtual void			drawGameOver(int winner, rect boomRect);


	SDL_Rect				toSDLRect(rect r);
	
	void					renderText(const char *text, int x, int y, bool selection);
};
