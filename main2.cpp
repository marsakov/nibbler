#include "Game.h"

int main()
{
	Game game;
    game.run();
    return 0;
}

//clang++ -std=c++ -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib main2.cpp Game.cpp