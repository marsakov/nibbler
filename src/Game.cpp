#include "../inc/Game.hpp"
// #include "../libSFMLSound/SoundSFML.hpp"

Game::Game() {
	snake1 = new Snake(1000, 800);
	snake2 = new Snake(1000, 800);
	libNum = num1;
	buttonNum = 1;
	menu = true;
	start = false;
	multiplayer = false;
	speed = 15;
}

Game::Game(int w, int h) {
	snake1 = new Snake(w, h);
	snake2 = new Snake(w, h);
	libNum = num1;
	buttonNum = 1;
	menu = true;
	start = false;
	multiplayer = false;
	speed = 15;
	ext_library2 = dlopen("libSFMLSound/libSFMLSound.so", RTLD_LAZY);
	creatS = (create_s*)dlsym(ext_library2,"createSound");
	destroyS = (destroy_s*)dlsym(ext_library2,"destroySound");
	soundLib = creatS();
}

Game::~Game() {
	dlclose(ext_library);
}

void	Game::closeLib() {
	std::cout << "closeLib" << std::endl;
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
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		exit(1);
	};

	creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	dynLib = creat(snake1, snake2);
	if (multiplayer)
	{
		dynLib->setMultiplayer(true);
		std::cout << "multiplayer on" << std::endl;
	}
	else
	{
		dynLib->setMultiplayer(false);
		std::cout << "multiplayer OFF" << std::endl;
	}
}

bool	Game::newGame() {

	Snake *newSnake = new Snake(snake1->screenWidth, snake1->screenHeiht);
	delete snake1;
	snake1 = newSnake;

	if (multiplayer) {
		start = false;
		newSnake = new Snake(snake1->screenWidth, snake1->screenHeiht);
		delete snake2;
		snake2 = newSnake;

		for (int i = 0; i < 4; i++)
			snake2->snakeRect[i].y += 100;

	}

	closeLib();
	getLib(libNum);

	return (true);
}

void	Game::keyHandle(eKeyType key) {
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
	else if (!menu && key >= up && key <= right)
		snake1->choseDirection(key);
	else if (!menu && multiplayer && key >= w && key <= d)
		snake2->choseDirection(key);
	else if (menu) {
		switch (key) {
			case (up):		{
				(buttonNum == 1) ? buttonNum = 4 : buttonNum--;
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (down):	{
				(buttonNum == 4) ? buttonNum = 1 : buttonNum++; 
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (left):	{
				(speed != 10) ? speed-- : 0;
				soundLib->set_switch_menu_sound(true);
				break;
			}
			case (right):	{
				soundLib->set_switch_menu_sound(true);
				(speed != 25) ? speed++ : 0;
				break;
			}
			// case (escape):	{ 
			// 	menu = false;
			// 	soundLib->set_change_sound(true);
			// 	break;
			// }
			case (enter): {
				switch (buttonNum) {
					case 1 : {
						soundLib->set_continue_music(true);
						soundLib->set_menu(false);
						soundLib->set_change_sound(true);
						menu = false;
						start = true;
						break ;
					}
					case 2 : {
						soundLib->set_menu(false);
						soundLib->set_change_sound(true);
						newGame();
						menu = false;
						start = true;
						break ;
					}
					case 3 : {
						if (multiplayer) {
							multiplayer = false;
							dynLib->setMultiplayer(false);
							std::cout << "multiplayer OFF" << std::endl;
						}
						else {
							std::cout << "multiplayer on" << std::endl;
							multiplayer = true;
							dynLib->setMultiplayer(true);
						}
						start = false ;
						break; 
					}
					case 4 : dynLib->close("EXIT"); break ;
				}
			}
			default : break ;
		}
	}
	dynLib->setKey(none);
}

void	Game::generateApple() {
	bool noCollision = false;

	while (!noCollision) 
	{
		appleRect.x = (rand() % (snake1->screenWidth / 100 - 1) + 1) * 100;
		appleRect.y = (rand() % (snake1->screenHeiht / 100 - 1) + 1) * 100;
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
		
		noCollision = true;
		for (int i = 0; i < snake1->snakeRect.size(); i++)
			if (snake1->snakeRect[i].x == appleRect.x && snake1->snakeRect[i].y == appleRect.y)
				noCollision = false;
		if (multiplayer) {
			for (int i = 0; i < snake2->snakeRect.size(); i++)
				if (snake2->snakeRect[i].x == appleRect.x && snake2->snakeRect[i].y == appleRect.y)
					noCollision = false;
		}
	}
	std::cout << "APPLE x = " << appleRect.x << " y = " << appleRect.y << std::endl;
}

bool	Game::checkCollision() {

	if (snake1->snakeRect[0].x == appleRect.x && snake1->snakeRect[0].y == appleRect.y)
	{
		appleRect.x = -1000;
		appleRect.y = -1000;
		snake1->size++;
		std::cout << "snake1->size = " << snake1->size << std::endl;
		soundLib->set_eat_sound(true);
	}
	else if (multiplayer && snake2->snakeRect[0].x == appleRect.x && snake2->snakeRect[0].y == appleRect.y) {
		appleRect.x = -1000;
		appleRect.y = -1000;
		snake2->size++;
		std::cout << "snake2->size = " << snake2->size << std::endl;
		soundLib->set_eat_sound(true);
	}

	for (int i = 1; i < snake1->snakeRect.size(); i++) {
		if (snake1->snakeRect[0].x == snake1->snakeRect[i].x && snake1->snakeRect[0].y == snake1->snakeRect[i].y) 
			return (false);
		else if (multiplayer && snake2->snakeRect[0].x == snake1->snakeRect[i].x && snake2->snakeRect[0].y == snake1->snakeRect[i].y) {
			snake1->snakeRect.resize(i);
			snake1->size = i;
		}
	}

	if (multiplayer) {
		if (snake1->snakeRect[0].x == snake2->snakeRect[0].x && snake1->snakeRect[0].y == snake2->snakeRect[0].y)
			return (false);
		for (int i = 1; i < snake2->snakeRect.size(); i++) {
			if (snake2->snakeRect[0].x == snake2->snakeRect[i].x && snake2->snakeRect[0].y == snake2->snakeRect[i].y)
				return (false);
			else if (snake1->snakeRect[0].x == snake2->snakeRect[i].x && snake1->snakeRect[0].y == snake2->snakeRect[i].y) {
				snake2->size = i;
				snake2->snakeRect.resize(i);
			}
		}
	}
	return (true);
}

void	Game::mainCycle() {
	size_t i = 0;

	generateApple();
	getLib(libNum);
	
	while (dynLib->windIsOpen()) {
		// soundLib->Sound();
		if (!menu && (i % (15 - (speed - 15)) == 0 && !snake1->moveSnake() )){
			std::cout << "snake outside the box" << std::endl;
			soundLib->set_game_over(true);
			usleep(1000000);
			soundLib->set_menu(true);
			soundLib->set_change_sound(true);
			start = false;
			menu = true;
		}
		if (multiplayer && !menu && (i % (15 - (speed - 15)) == 0 && !snake2->moveSnake() )) {
			std::cout << "snake outside the box" << std::endl;
			// в отдельную функцию


			// выключить музыку 
			// включить звук БУМ

			soundLib->set_game_over(true);
			usleep(1000000);
			// включить музыку меню
			soundLib->set_menu(true);
			soundLib->set_change_sound(true);
			start = false;
			menu = true;
		}
		if (!menu && (i % 750 == 0 || appleRect.x == -1000))
			generateApple();

		dynLib->handleEvent();
		keyHandle(dynLib->getKey());

		if (!menu && !checkCollision()) {
			std::cout << "boom" << std::endl;
			usleep(1000000);
			soundLib->set_menu(true);
			soundLib->set_change_sound(true);
			start = false;
			menu = true;
		}

		if (menu)
			dynLib->drawMenu(buttonNum, start, speed);
		else
			dynLib->draw(appleRect);
		soundLib->Sound();
		if ( i == 2000000000 )
			i = 0;
		if (!menu)
			i++;
	}
}

