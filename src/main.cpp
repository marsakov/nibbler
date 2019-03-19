#include "../inc/Game.hpp"
#include <regex>
// #include "../libSFMLSound/SoundSFML.hpp"



int main(int argc, char *argv[])
{

	int w;
	int h;
	std::string ip;

	if (argc == 4) {
		ip = argv[3];
	}
	else if (argc != 3) {
		std::cout << "Usage:\n./ nibbler [width] [height]\nsize must be integer" << std::endl;
		exit(1);
	}

	try {
		w = std::stoi( argv[1] ) / 50 * 50;
		h = std::stoi( argv[2] ) / 50 * 50;
	}
	catch (std::exception e) {
		std::cout << "Usage:\n./ nibbler [width] [height] [IP]\nsize must be integer" << std::endl;
		exit(1);
	}

	if (w < 1000 || w > 2500 || h < 800 || h > 1300 ) {
		std::cout << "1000 < width < 2500\n800 < height < 1300" << std::endl;
		exit(1);
	}

	if (argc == 4) {
		Game game(w, h, ip);
		game.mainCycle();
	}
	else {
		Game game(w, h);
		game.mainCycle();
	}

	return (0);
}