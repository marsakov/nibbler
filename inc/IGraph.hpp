#pragma once

#include "Snake.hpp"

class IGraph
{

protected:
	Snake *snake;

public:

	virtual ~IGraph() {} ;

	virtual int		close(std::string msg) = 0;
	virtual void	init() = 0;
	virtual void	draw() = 0;
	virtual int		move() = 0;
	virtual bool	windIsOpen() = 0;
	virtual int		handleEvent() = 0;
	
};
