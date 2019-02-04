#pragma once

#include <dlfcn.h>
#include "IGraph.hpp"
#include "Snake.hpp"

class Game
{
	int				SCREEN_WIDTH;
	int				SCREEN_HEIGHT;
	void			*ext_library;
	typedef IGraph*	create_t(int, int, Snake*);
	typedef void	destroy_t(IGraph*);
	create_t*		creat;
	destroy_t*		destroy;

public:
	IGraph			*dynLib;

	Game();
	Game(int w, int h);
	~Game();
	
	void	getLib(int libNum, Snake *s);
	void	closeLib();
};