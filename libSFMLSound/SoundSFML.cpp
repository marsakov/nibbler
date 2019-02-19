#include "SoundSFML.hpp"
//clang++ src/SoundSFML.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -rpath ~/.brew/lib src/main.cpp src/Game.cpp src/Snake.cpp
#include <iostream>
#include <SFML/Audio.hpp>

sf::SoundBuffer menuBuffer, eatBuffer;
sf::Music music_menu, music_game;

SoundSFML::SoundSFML() {
	// sf::SoundBuffer menuBuffer, eatBuffer;
	// sf::Music music_menu, music_game;
	std::cout << "SoundSFML::SoundSFML()" << std::endl;
	init();
}


// SoundSFML::SoundSFML(SoundSFML &obj) {
// 	*this = obj;
// }

SoundSFML::~SoundSFML() {

}

void	SoundSFML::init() {

	// sf::SoundBuffer menuBuffer, eatBuffer; // create buff
	menuBuffer.loadFromFile("resources/+.ogg"); //wav, ogg              load sound
	eatBuffer.loadFromFile("resources/eat.ogg"); 
	sf::Sound menu(menuBuffer); // create sound
	sf::Sound eat(eatBuffer);
	//if ()
	eat.play(); //make sound
	menu.play(); //make sound

	//sf::Music music_menu, music_game;
	music_menu.openFromFile("resources/menu.ogg");
	music_menu.play(); 
	music_menu.setLoop(true); // loop


	// if (game.menu) {
	// 	music_game.openFromFile("game.ogg");
	// 	music_game.play(); 
	// 	music_game.setLoop(true); // loop
	// }
	std::cout << "SoundSFML::init()" << std::endl;
	//========================================================
	
}




	



extern "C" SoundSFML *createSound() {
	return (new SoundSFML());
}


extern "C"	void destroySound(SoundSFML *g) {
	delete g;
}