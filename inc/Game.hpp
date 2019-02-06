#pragma once

#include <dlfcn.h>
#include "IGraph.hpp"
#include "Snake.hpp"

class Game
{
	eKeyType		libNum;
	void			*ext_library;
	typedef IGraph*	create_t(Snake*);
	typedef void	destroy_t(IGraph*);
	create_t*		creat;
	destroy_t*		destroy;
	IGraph			*dynLib;
	Snake			*snake;
	bool			menu;
	bool			start;
	int				buttonNum;

public:

	Game();
	Game(int w, int h);
	~Game();
	
	void	keyHandle(eKeyType key);
	void	getLib(eKeyType key);
	void	closeLib();
	void	mainCycle();
};