#include "../inc/Game.hpp"

Game::Game() {
	buttonNum = 1;
	snake = new Snake(1000, 800);
	libNum = num1;
	menu = true;
	start = false;
}

Game::Game(int w, int h) {
	snake = new Snake(w, h);
	libNum = num1;
	menu = true;
	start = false;
	buttonNum = 1;
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
			ext_library = dlopen("libSDL.so", RTLD_LAZY);
			break ;
		}
		case num2: {
			ext_library = dlopen("libSFML.so", RTLD_LAZY); break ;
		}
		default : {
			ext_library = dlopen("libSFML.so", RTLD_LAZY); break ;
		}
	}
	
	if (!ext_library) {
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		exit(1);
	};

	creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	dynLib = creat(snake);
}

void	Game::keyHandle(eKeyType key) {
	
	if (key >= num1 && key <= num3 && libNum != key) {
		libNum = key;
		closeLib();
		getLib(key);
	}
	else if (!menu && key == escape)
		menu = true;
	else if (!menu && key >= up && key <= right)
		snake->choseDirection(key);
	else if (menu) {
		switch (key) {
			case (up):		(buttonNum == 1) ? buttonNum = 4 : buttonNum--; break;
			case (down):	(buttonNum == 4) ? buttonNum = 1 : buttonNum++; break;
			case (left):	(snake->snakeSpeed != 10) ? snake->snakeSpeed-- : 0; break;
			case (right):	(snake->snakeSpeed != 25) ? snake->snakeSpeed++ : 0; break;
			case (escape):	menu = false; break;
			case (enter): {
				switch (buttonNum) {
					case 1 : {
						menu = false;
						start = true;
						break ;
					}
					case 2 : {
						menu = false;
						start = true;
						int w = snake->SCREEN_WIDTH;
						int h = snake->SCREEN_HEIGHT;
						int s = snake->snakeSpeed;
						delete snake;
						snake = new Snake(w, h);
						snake->snakeSpeed = s;
						closeLib();
						getLib(libNum);
						break ;
					}
					case 4 : dynLib->close("EXIT"); break ;
				}
			}
			default : break ;
		}
	}
}


void	Game::mainCycle() {
	size_t i = 0;
	eKeyType key;

	getLib(libNum);
	while (dynLib->windIsOpen()) {

		if (!menu && (i % (15 - (snake->snakeSpeed - 15)) == 0 && !snake->moveSnake() )){
			std::cout << "snake outside the box" << std::endl;
			exit(1);
		}
		if (!menu && (i % 750 == 0 || snake->appleRECT.x == -1000))
			snake->generateApple();

		key = dynLib->handleEvent();
		if (key != none)
			keyHandle(key);

		if (!menu && !snake->checkCollision()) {
			std::cout << "boom" << std::endl;
			exit(1);
		}
		if (menu)
			dynLib->drawMenu(buttonNum, start);
		else
			dynLib->draw();
		if ( i == 2000000000 )
			i = 0;
		if (!menu)
			i++;
	}
}

