#pragma once

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <iostream>
#include <unistd.h>
#include <stdio.h> 

#define PORT 8080 
#define SA struct sockaddr 

#include <dlfcn.h>
#include <unistd.h>
#include "IGraph.hpp"
#include "../libSFMLSound/ISound.hpp"
#include "Snake.hpp"
#include "Network.hpp"

#include <sys/time.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

class Game
{
	size_t				iter;
	eKeyType			libNum;
	void				*ext_library;
	void				*ext_library2;
	typedef IGraph*		create_t(Snake*, Snake*);
	typedef void		destroy_t(IGraph*);
	typedef ISound*		create_s();
	typedef void		destroy_s(ISound*);
	create_t*			creat;
	destroy_t*			destroy;
	create_s*			creatS;
	destroy_s*			destroyS;
	IGraph				*dynLib;
	ISound				*soundLib;
	Snake				*snake1;
	Snake				*snake2;
	int					speed;
	bool				menu;
	bool				start;
	int					buttonNum;
	rect				appleRect;
	rect				boomRect;
	int					winner;
	int					gameOverCount;
	bool				server;
	bool 				client;
	eKeyType			keyToNetwork;
	std::string			idClient;
	Network				*network;
	bool				iAmReady;
	bool				connectIsReady;
	rect                appleFromServer;


public:
	void					netGame(void);
	void					clientGame(void);
	void					sendNet(int command);
	int						recvNet(void);


	Game();
	Game(int w, int h);
	Game(int w, int h, std::string ip);
	~Game();
	
	void	init();
	void	keyHandle(eKeyType key);
	void	getLib(eKeyType key);
	void	closeLib();
	void	mainCycle();
	void	generateApple();
	bool	checkCollision();
	bool	newGame();
	void	gameOver();
	void	createServer();

};