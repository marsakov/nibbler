// #include "../inc/SFMLGraph.hpp"
#include <dlfcn.h>
#include "../inc/IGraph.hpp"

IGraph *getLib(int libNum, int w, int h, Snake *snake) {
	void			*ext_library;
	typedef IGraph*	create_t(int, int, Snake*);
	typedef void	destroy_t(IGraph*);

	switch (libNum){
		case 1: {
			ext_library = dlopen("libSDL.so", RTLD_LAZY);
			w /= 2;
			h /= 2;
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

	create_t* creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy_t* destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	return (creat(w, h, snake));
}

int main(int argc, char *argv[])
{
	IGraph *dynlib;
	Snake *snake = new Snake(5120/2, 2880/2);
	size_t i = 0;
	int libNum = 1;
	int newLibNum;

	dynlib = getLib(libNum, 5120/2, 2880/2, snake);
	snake->generateApple();
	while (dynlib->windIsOpen()) {
		if (i % 15 == 0) {
			if (!snake->moveSnake()){
				std::cout << "snake outside the box" << std::endl;
				exit(1);
			}
		}
		if (i % 750 == 0 || snake->appleRECT.x == -1000)
			snake->generateApple();
		newLibNum = dynlib->handleEvent();
		if (newLibNum && newLibNum != libNum)
			dynlib = getLib(newLibNum, 5120/2, 2880/2, snake);
		if (!snake->checkCollision()) {
			std::cout << "boom" << std::endl;
			exit(1);
		}
		dynlib->draw();
		i++;
	}

	// dlclose(ext_library);
	return (0);
}