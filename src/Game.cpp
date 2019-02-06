#include "../inc/Game.hpp"

Game::Game() {

}

Game::Game(int w, int h) {
	snake = new Snake(w, h);
	libNum = num1;
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
			case (up):		(buttonNum == 1) ? buttonNum = 3 : buttonNum--; break;
			case (down):	(buttonNum == 3) ? buttonNum = 1 : buttonNum++; break;
			case (escape):	dynLib->close("EXIT"); break;
			case (enter): {
				switch (buttonNum) {
					case 1 : menu = false; break ;
					case 2 : {
						int w = snake->SCREEN_WIDTH;
						int h = snake->SCREEN_HEIGHT;
						delete snake;
						snake = new Snake(w, h);
						break ;
					}
					case 3 : dynLib->close("EXIT");
					break ;
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
	snake->generateApple();
	while (dynLib->windIsOpen()) {

		if (!menu && (i % 15 == 0 && !snake->moveSnake() )){
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
			dynLib->drawMenu();
		else
			dynLib->draw();
		if ( i == 2000000000 )
			i = 0;
		i++;
	}
}

