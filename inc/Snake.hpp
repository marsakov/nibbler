#pragma once

#include <iostream>
#include <vector>

typedef struct	rect
{
	int		x;
	int		y;
	double	w;
	double	h;
	int 	s;
	double	r;
	double	g;
	double	b;

}				rect;


enum eKeyType
{
	w,
	s,
	a,
	d,
	up,
	down,
	left,
	right,
	escape,
	enter,
	num1,
	num2,
	num3,
	ready,
	mute,
	refresh,
	none
};

class Snake
{

public:
	int					screenWidth;
	int					screenHeiht;
	std::vector<rect>	snakeRect;
	char				direction;
	int					size;
	int					step;
	rect				pieceRect;

	eKeyType			key;

	bool				waiting;
	bool				multiplayer;
	bool				network;
	bool				muteVar;

	Snake(int width, int height);
	Snake(Snake &obj);
	~Snake();

	void	choseDirection(eKeyType keyType);
	bool	moveSnake();

};