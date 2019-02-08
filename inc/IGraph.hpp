#pragma once

#include "Snake.hpp"

class IGraph
{

public:

	bool					multiplayer;
	virtual ~IGraph() {} ;

	virtual int				close(std::string msg) = 0;
	virtual void			init() = 0;
	virtual void			draw(rect appleRect) = 0;
	virtual void			drawMenu(int buttonNum, bool start, int speed) = 0;
	virtual eKeyType		getKey() = 0;
	virtual bool			windIsOpen() = 0;
	virtual eKeyType		handleEvent() = 0;
	
};
