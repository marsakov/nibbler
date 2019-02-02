// #include "../inc/SFMLGraph.hpp"
#include <dlfcn.h>
#include "../inc/IGraph.hpp"

int main(int argc, char *argv[])
{
	void *ext_library;
	typedef IGraph* create_t(int, int);
	typedef void destroy_t(IGraph*);

	ext_library = dlopen("libSFML.so", RTLD_LAZY);
	if (!ext_library){
		//если ошибка, то вывести ее на экран
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		exit(1); // в случае ошибки можно, например, закончить работу программы
	};

	create_t* creat = (create_t*)dlsym(ext_library,"createGraph");
	destroy_t* destroy = (destroy_t*)dlsym(ext_library,"destroyGraph");

	IGraph *dynlib = creat(2000, 1600);

	size_t i = 0;

	dynlib->generateApple();
	while (dynlib->windIsOpen()) {
		if (i % 15 == 0)
			dynlib->moveSnake();
		if (i % 750 == 0 || appleRECT.x == -1000)
			dynlib->generateApple();
		dynlib->handleEvent();
		dynlib->checkCollision();
		dynlib->draw();
		i++;
		if (i == 2000000000)
			i = 0;
	}

	// dynlib->mainCycle();

	dlclose(ext_library);

	// SFMLGraph sdl;
	
	// sdl.mainCycle();
	// system("leaks a.out");
	return (0);
}