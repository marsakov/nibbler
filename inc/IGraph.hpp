#pragma once

#include "Snake.hpp"

class IGraph
{
protected:
	eKeyType				key;

public:
	virtual ~IGraph() {} ;

	virtual int				close(std::string msg) = 0;
	virtual void			init() = 0;
	virtual void			draw(rect appleRect) = 0;
	virtual void			drawMenu(int buttonNum, bool start, bool network, int speed) = 0;
	virtual void			drawGameOver(int winner, rect boomRect) = 0;
	virtual bool			windIsOpen() = 0;
	virtual void			handleEvent() = 0;
	virtual void			setKeyDown() = 0;
	virtual eKeyType		getKey() = 0;
	virtual void			setKey(eKeyType k) = 0;
};
