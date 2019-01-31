#include "SFMLGraph.hpp"
#include <dlfcn.h>

int main(int argc, char *argv[])
{
	// void *ext_library;
	// void (*powerfunc)(void);

	// ext_library = dlopen("lib1.so",RTLD_LAZY);
	// if (!ext_library){
	// 	//если ошибка, то вывести ее на экран
	// 	fprintf(stderr,"dlopen() error: %s\n", dlerror());
	// 	exit(1); // в случае ошибки можно, например, закончить работу программы
	// };

	// powerfunc = dlsym(ext_library, "mainCycle");

	// (*powerfunc)();

	// dlclose(ext_library);

	SFMLGraph sdl;
	
	sdl.mainCycle();
	system("leaks a.out");
	return (0);
}