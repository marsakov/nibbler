#include "../inc/Game.hpp"

Game::Game() {

}

Game::Game(int w, int h) {
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
}

Game::~Game() {
	dlclose(ext_library);
}

void	Game::closeLib() {
	std::cout << "closeLib" << std::endl;
	delete dynLib;
	dynLib = NULL;
	destroy(dynLib);
}

void	Game::getLib(int libNum, Snake *s) {

	switch (libNum){
		case 1: {
			ext_library = dlopen("libSDL.so", RTLD_LAZY);
			// Snake.SCREEN_WIDTH /= 2;
			// Snake.SCREEN_HEIGHT /= 2;
			break ;
		}
		case 2:
			ext_library = dlopen("libSFML.so", RTLD_LAZY); break ;
		default :
			ext_library = dlopen("libSDL.so", RTLD_LAZY); break ;
	}
	
	if (!ext_library) {
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		exit(1);
	};

	creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	dynLib = creat(SCREEN_WIDTH, SCREEN_HEIGHT, s);
}

