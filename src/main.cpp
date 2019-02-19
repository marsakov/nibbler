#include "../inc/Game.hpp"
#include "../libSFMLSound/SoundSFML.hpp"



int main(int argc, char *argv[])
{

	int w;
	int h;

	if (argc != 3) {
		std::cout << "Usage:\n./ nibbler [width] [height]\nsize must be integer" << std::endl;
		exit(1);
	}
	try {
		w = std::stoi( argv[1] ) / 50 * 50;
		h = std::stoi( argv[2] ) / 50 * 50;
	}
	catch (std::exception e) {
		std::cout << "Usage:\n./ nibbler [width] [height]\nsize must be integer" << std::endl;
		exit(1);
	}
	if (w < 1000 || w > 2500 || h < 800 || h > 1300 ) {
		std::cout << "1000 < width < 2500\n800 < height < 1300" << std::endl;
		exit(1);
	}

	Game game(w, h);
	// // SoundSFML s;
	// // s.init();
	// std::cout << "main.cpp SoundSFML s.init()" << std::endl;
	game.mainCycle();
	return (0);
}