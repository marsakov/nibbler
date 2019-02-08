#pragma once

#include <dlfcn.h>
#include <unistd.h>
#include "IGraph.hpp"
#include "Snake.hpp"

class Game
{
	eKeyType		libNum;
	void			*ext_library;
	typedef IGraph*	create_t(Snake*, Snake*);
	typedef void	destroy_t(IGraph*);
	create_t*		creat;
	destroy_t*		destroy;
	IGraph			*dynLib;
	Snake			*snake1;
	Snake			*snake2;
	int				speed;
	bool			multiplayer;
	bool			menu;
	bool			start;
	int				buttonNum;
	rect			appleRect;

public:

	Game();
	Game(int w, int h);
	~Game();
	
	void	keyHandle(eKeyType key);
	void	getLib(eKeyType key);
	void	closeLib();
	void	mainCycle();
	void	generateApple();
	bool	checkCollision();
	bool	newGame();

};