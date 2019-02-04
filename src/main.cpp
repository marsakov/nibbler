#include "../inc/Game.hpp"


int main(int argc, char *argv[])
{
	Snake *snake = new Snake(5120/2, 2880/2);
	Game game(5120/2, 2880/2);

	size_t i = 0;
	int libNum = 2;
	int newLibNum;

	game.getLib(libNum, snake);
	snake->generateApple();
	while (game.dynLib->windIsOpen()) {
		if (i % 15 == 0) {
			if (!snake->moveSnake()){
				std::cout << "snake outside the box" << std::endl;
				exit(1);
			}
		}
		if (i % 750 == 0 || snake->appleRECT.x == -1000)
			snake->generateApple();
		newLibNum = game.dynLib->handleEvent();
		if (newLibNum && newLibNum != libNum) {
			game.closeLib();
			game.getLib(newLibNum, snake);
		}
		if (!snake->checkCollision()) {
			std::cout << "boom" << std::endl;
			exit(1);
		}
		game.dynLib->draw();
		i++;
	}

	return (0);
}