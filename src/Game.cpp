#include "../inc/Game.hpp"
#include <time.h>

using namespace std::chrono;

void	Game::init() {
	libNum = num1;
	buttonNum = 2;
	menu = true;
	start = false;
	snake1->multiplayer = false;
	snake1->network = false;
	server = false;
	client = false;
	keyToNetwork = none;
	speed = 15;
	network = NULL;
	winner = 1;

	ext_library2 = dlopen("libSFMLSound/libSFMLSound.so", RTLD_LAZY);
	creatS = (create_s*)dlsym(ext_library2,"createSound");
	destroyS = (destroy_s*)dlsym(ext_library2,"destroySound");
	soundLib = creatS();

	snake1->snakeRect[0].r = 0.97f;
	snake1->snakeRect[0].g = 0.14f;
	snake1->snakeRect[0].b = 0.45f;
	snake2->snakeRect[0].r = 0.98f;
	snake2->snakeRect[0].g = 0.58f;
	snake2->snakeRect[0].b = 0.12f;

	appleFromServer.x = 150;
	appleFromServer.y = 150;
}

Game::Game() {
	init();
	snake1 = new Snake(1000, 800);
	snake2 = new Snake(1000, 800);
}

Game::Game(int w, int h) {
	snake1 = new Snake(w, h);
	snake2 = new Snake(w, h);
	init();
}

Game::Game(int w, int h, std::string id) {
	snake1 = new Snake(w, h);
	snake2 = new Snake(w, h);
	init();
	snake1->multiplayer = true;
	client = true;
	snake1->network = true;
	idClient = id;
	network = new Network(idClient);
}

Game::~Game() {
	dlclose(ext_library);
	system("leaks nibbler");
}


void	Game::createServer() {
	if (!network)
		network = new Network(true);
}


void	Game::closeLib() {
	// std::cout << "closeLib" << std::endl;
	destroy(dynLib);
}

void	Game::getLib(eKeyType key) {
	switch (key){
		case num1: {
			ext_library = dlopen("libSDL/libSDL.so", RTLD_LAZY); break ;
		}
		case num2: {
			ext_library = dlopen("libSFML/libSFML.so", RTLD_LAZY); break ;
		}
		case num3: {
			ext_library = dlopen("libOpenGL/libOpenGL.so", RTLD_LAZY); break ;
		}
		default : {
			ext_library = dlopen("libSFML/libSFML.so", RTLD_LAZY); break ;
		}
	}
	
	if (!ext_library) {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		exit(1);
	};

	creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	dynLib = creat(snake1, snake2);

}

bool	Game::newGame() {
	Snake *newSnake = new Snake(snake1->screenWidth, snake1->screenHeiht);
	newSnake->snakeRect[0].r = snake1->snakeRect[0].r;
	newSnake->snakeRect[0].g = snake1->snakeRect[0].g;
	newSnake->snakeRect[0].b = snake1->snakeRect[0].b;
	newSnake->multiplayer = snake1->multiplayer;
	newSnake->network = snake1->network;
	newSnake->muteVar = snake1->muteVar;
	delete snake1;
	snake1 = newSnake;

	if (snake1->multiplayer) {
		newSnake = new Snake(snake1->screenWidth, snake1->screenHeiht);
		newSnake->snakeRect[0].r = snake2->snakeRect[0].r;
		newSnake->snakeRect[0].g = snake2->snakeRect[0].g;
		newSnake->snakeRect[0].b = snake2->snakeRect[0].b;
		delete snake2;
		snake2 = newSnake;

		for (int i = 0; i < 4; i++)
			snake2->snakeRect[i].y += 100;

	}

	closeLib();
	getLib(libNum);

	iter = 0;
	menu = false;
	start = true;
	soundLib->set_menu(menu);
	soundLib->set_change_sound(true);

	soundLib->set_new_game(true);
	iAmReady = false;
	connectIsReady = false;

	return (true);
}

void	Game::keyHandle(eKeyType key) {

	keyToNetwork = key;

	if (!menu)
		soundLib->set_menu(false);
	
	if (key >= num1 && key <= num3 && libNum != key) {
		libNum = key;
		closeLib();
		getLib(key);
	}
	else if (!menu && key == escape) {
		menu = true;
		soundLib->set_menu(true);
		soundLib->set_change_sound(true);
	}
	else if (!menu && key >= up && key <= right) {
		if (snake1->network && client)
			snake2->key = key;
		else
			snake1->key = key;
	}
	else if (!menu && snake1->multiplayer && key >= w && key <= d) {
		if (snake1->network && client)
			snake1->key = key;
		else
			snake2->key = key;
	}
	else if (menu) {
		switch (key) {
			case (up):		{
				((buttonNum == 2 && (!start || network)) || (buttonNum == 1 && start)) ? buttonNum = 4 : buttonNum--;
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (down):	{
				(buttonNum == 4) ? buttonNum = ((!start || network) ? 2 : 1) : buttonNum++; 
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (left):	{
				(speed != 10 && !client) ? speed-- : 0;
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (right):	{
				soundLib->set_switch_menu_sound(true);
				(speed != 25 && !client) ? speed++ : 0;
				break;
			}
			case (enter): {
				switch (buttonNum) {
					case 1 : {
						soundLib->set_menu(false);
						soundLib->set_change_sound(true);
						menu = false;
						start = true;
						break ;
					}
					case 2 : {
						if (snake1->network && server && !network) {
							createServer();
							break ;
						}
						else if (snake1->network && network && connectIsReady) {
							keyToNetwork = ready;
							if (client)
								// network->cycle(&(snake2->snakeRect), &(snake1->snakeRect), &keyToNetwork);
								network->cycle(&keyToNetwork, &(appleFromServer.x), &(appleFromServer.y));
							else
								// network->cycle(&(snake1->snakeRect), &(snake2->snakeRect), &keyToNetwork);
								network->cycle(&keyToNetwork, &(appleRect.x), &(appleRect.y));

							connectIsReady = false;
							std::cout << "connectIsReady" << std::endl;
							usleep(34000);
						}
						else if (snake1->network && network) {
							iAmReady = true;
							keyToNetwork = ready;
							if (client)
								// network->cycle(&(snake2->snakeRect), &(snake1->snakeRect), &keyToNetwork);
								network->cycle(&keyToNetwork, &(appleFromServer.x), &(appleFromServer.y));
							else
								// network->cycle(&(snake1->snakeRect), &(snake2->snakeRect), &keyToNetwork);
								network->cycle(&keyToNetwork, &(appleRect.x), &(appleRect.y));

							snake1->waiting = true;
							std::cout << "iAmReady" << std::endl;
							break ;
						}
						newGame();
						break ;
					}
					case 3 : {
						if (snake1->network && client)
							break;
						else {
							if (!snake1->multiplayer) {
								std::cout << "multiplayer on" << std::endl;
								snake1->multiplayer = true;
							}
							else if (snake1->multiplayer && !snake1->network) {
								server = true;
								snake1->network = true;
								std::cout << "multiplayer NET" << std::endl;
							}
							else {
								snake1->multiplayer = false;
								snake1->network = false;
								std::cout << "multiplayer OFF" << std::endl;
							}
							start = false ;
							break;
						}
					}
					case 4 : dynLib->close("EXIT"); break ;
				}
			}
			default : break ;
		}
	}
	if (key == mute) {
		if (snake1->muteVar && soundLib->get_mute()) {
			snake1->muteVar = false;
			soundLib->set_mute(false);
		} else  {
			snake1->muteVar = true;
			soundLib->set_mute(true);
		}
	}
	dynLib->setKey(none);
}

void	Game::generateApple() {
	bool noCollision = false;
	std::cout << "Refresh Apple" << std::endl;

	appleRect.s = rand() % 2;
	switch (rand() % 4) {
		case 0: {
			appleRect.r = 0.67f;
			appleRect.g = 0.49f;
			appleRect.b = 1;
			break ;
		}
		case 1: {
			appleRect.r = 0.41f;
			appleRect.g = 0.85f;
			appleRect.b = 0.94f;
			break ;
		}
		case 2: {
			appleRect.r = 0.65f;
			appleRect.g = 0.89f;
			appleRect.b = 0.17f;
			break ;
		}
		case 3: {
			appleRect.r = 1.0f;
			appleRect.g = 0.97f;
			appleRect.b = 0.3f;
			break ;
		}
	}

	if (client) {
		appleRect.x = appleFromServer.x;
		appleRect.y = appleFromServer.y;
		return ;
	}

	while (!noCollision) 
	{
		appleRect.x = (rand() % (snake1->screenWidth / 100 - 1) + 1) * 100;
		appleRect.y = (rand() % (snake1->screenHeiht / 100 - 1) + 1) * 100;
		
		noCollision = true;
		for (int i = 0; i < snake1->snakeRect.size(); i++)
			if (snake1->snakeRect[i].x == appleRect.x && snake1->snakeRect[i].y == appleRect.y)
				noCollision = false;
		if (snake1->multiplayer) {
			for (int i = 0; i < snake2->snakeRect.size(); i++)
				if (snake2->snakeRect[i].x == appleRect.x && snake2->snakeRect[i].y == appleRect.y)
					noCollision = false;
		}
	}
}

bool	Game::checkCollision() {

	if (snake1->snakeRect[0].x == appleRect.x && snake1->snakeRect[0].y == appleRect.y)
	{
		appleRect.x = -1000;
		appleRect.y = -1000;
		snake1->size++;
		if (server)
			keyToNetwork = refresh;
		soundLib->set_eat_sound(true);
	}
	else if (snake1->multiplayer && snake2->snakeRect[0].x == appleRect.x && snake2->snakeRect[0].y == appleRect.y) {
		appleRect.x = -1000;
		appleRect.y = -1000;
		snake2->size++;
		if (client)
			keyToNetwork = refresh;
		soundLib->set_eat_sound(true);
	}

	for (int i = 1; i < snake1->snakeRect.size(); i++) {
		if (snake1->snakeRect[0].x == snake1->snakeRect[i].x && snake1->snakeRect[0].y == snake1->snakeRect[i].y) {
			boomRect.x = snake1->snakeRect[0].x;
			boomRect.y = snake1->snakeRect[0].y;
			winner = 2;
			return (false);
		}
		else if (snake1->multiplayer && snake2->snakeRect[0].x == snake1->snakeRect[i].x && snake2->snakeRect[0].y == snake1->snakeRect[i].y) {
			snake1->snakeRect.resize(i);
			snake1->size = i;
			soundLib->set_eat_sound(true);
		}
	}

	if (snake1->multiplayer) {
		if (snake1->snakeRect[0].x == snake2->snakeRect[0].x && snake1->snakeRect[0].y == snake2->snakeRect[0].y) {
			winner = (snake1->size > snake2->size) ? 1 : 2;
			boomRect.x = snake1->snakeRect[0].x;
			boomRect.y = snake1->snakeRect[0].y;
			return (false);
		}
		for (int i = 1; i < snake2->snakeRect.size(); i++) {
			if (snake2->snakeRect[0].x == snake2->snakeRect[i].x && snake2->snakeRect[0].y == snake2->snakeRect[i].y) {
				boomRect.x = snake2->snakeRect[0].x;
				boomRect.y = snake2->snakeRect[0].y;
				winner = 1;
				return (false);
			}
			else if (snake1->snakeRect[0].x == snake2->snakeRect[i].x && snake1->snakeRect[0].y == snake2->snakeRect[i].y) {
				snake2->size = i;
				snake2->snakeRect.resize(i);
				soundLib->set_eat_sound(true);
			}
		}
	}
	return (true);
}

void	Game::gameOver() {
	soundLib->set_game_over(true);
	soundLib->set_menu(true);
	soundLib->set_change_sound(true);
	start = false;
	menu = true;
	buttonNum = 2;
	gameOverCount = 200;
}

void	Game::mainCycle() {
	iter = 0;
	generateApple();
	getLib(libNum);
	
	while (dynLib->windIsOpen()) {

		if (!menu && (iter % (15 - (speed - 15)) == 0 )){

			if ( !snake1->moveSnake() ) {
				winner = 2;
				boomRect.x = snake1->snakeRect[0].x;
				boomRect.y = snake1->snakeRect[0].y;
				gameOver();
			}
			if (snake1->multiplayer && !snake2->moveSnake() ) {
				boomRect.x = snake2->snakeRect[0].x;
				boomRect.y = snake2->snakeRect[0].y;
				winner = 1;
				gameOver();
			}
		}
		

		if (!menu && (iter % 750 == 0 || appleRect.x == -1000))
			generateApple();

		dynLib->handleEvent();
		if (!gameOverCount)
			keyHandle(dynLib->getKey());

		if (!menu && !checkCollision())
			gameOver();


		if (gameOverCount) {
			dynLib->drawGameOver(winner, boomRect);
			gameOverCount--;
		}
		else if (menu)
			dynLib->drawMenu(buttonNum, start, network, speed);
		else 
			dynLib->draw(appleRect);

		soundLib->Sound();

		if (!menu && snake1->network && network) {
			if (client)
				network->cycle(&keyToNetwork, &(appleFromServer.x), &(appleFromServer.y));
			else
				network->cycle(&keyToNetwork, &(appleRect.x), &(appleRect.y));

			if (keyToNetwork == ready && iAmReady) {
				snake1->waiting = false;
				newGame();
			}
			else if (keyToNetwork == ready)
				connectIsReady = true;
			else if (keyToNetwork == refresh) {
				if (client)
					snake1->size++;
				else
					snake2->size++;
				generateApple();
			}
			else if (keyToNetwork != none) {
				if (keyToNetwork >= up && keyToNetwork <= right && !menu)
					switch(keyToNetwork) {
						case up: keyToNetwork = w; break ;
						case down: keyToNetwork = s; break ;
						case left: keyToNetwork = a; break ;
						case right: keyToNetwork = d; break ;
						default : break;
					} 
				keyHandle(keyToNetwork);
			}
			keyToNetwork = none;
		}
		else if (snake1->network && network) {
			if (client)
				network->cycle(&keyToNetwork, &(appleFromServer.x), &(appleFromServer.y));
			else
				network->cycle(&keyToNetwork, &(appleRect.x), &(appleRect.y));

			if (keyToNetwork == ready && iAmReady) {
				snake1->waiting = false;
				newGame();
			}
			else if (keyToNetwork == ready)
				connectIsReady = true;
			else if (client && (keyToNetwork == right || keyToNetwork == left)) {
				if (keyToNetwork == left)
					(speed != 10) ? speed-- : 0;
				else
					(speed != 25) ? speed++ : 0;
			}
			keyToNetwork = none;
		}
		if ( iter == 2000000000 )
			iter = 0;
		if ( !menu )
			iter++;

	}
}

