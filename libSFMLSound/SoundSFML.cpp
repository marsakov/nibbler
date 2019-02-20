#include "SoundSFML.hpp"
//clang++ src/SoundSFML.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -rpath ~/.brew/lib src/main.cpp src/Game.cpp src/Snake.cpp
// #include <iostream>
// #include <SFML/Audio.hpp>

// sf::SoundBuffer 	menuBuffer, eatBuffer;
// sf::Music 			music_menu, music_game;

SoundSFML::SoundSFML() {
	std::cout << "SoundSFML::SoundSFML()" << std::endl;
	menu = true;
	change_sound = true;
	init();
}

SoundSFML::~SoundSFML() {
	
}

void 	SoundSFML::Sound() {

	// if (eat_sound) {
	// 	sf::Sound eat(eatBuffer);
	// 	eat.play(); //make sound
	// 	eat_sound = false;
	// 	std::cout << "eat_sound" << std::endl;
	// }
	// if (switch_menu_sound) {
	// 	sf::Sound menu_sound(menuBuffer); // create sound
	// 	menu_sound.play(); //make sound
	// 	switch_menu_sound = false;
	// 	std::cout << "switch_menu_sound" << std::endl;
	// }


	if (eat_sound) {
		// sf::Sound eat(eatBuffer);
		eat.play(); //make sound
		eat_sound = false;
		std::cout << "eat_sound" << std::endl;
	}
	if (switch_menu_sound) {
		// sf::Sound menu_sound(menuBuffer); // create sound
		menu_sound.play(); //make sound
		switch_menu_sound = false;
		std::cout << "switch_menu_sound" << std::endl;
	}

	if (change_sound) {
		std::cout << "CHANGE" << std::endl;
		if (menu) {
			music_game.pause();
			music_menu.play(); 
			music_menu.setLoop(true); // loop
			std::cout << "menu" << std::endl;
		}
		else {
			music_menu.pause(); 
			music_game.play(); 
			music_game.setLoop(true); // loop
			std::cout << "game" << std::endl;
		}
		change_sound = false;
	}
}

void	SoundSFML::init() {

	try {

		// music
		// music_menu.openFromFile("resources/menu.ogg");
		// music_game.openFromFile("resources/game.ogg");

		// sound
		menuBuffer.loadFromFile("resources/+.ogg");
		eatBuffer.loadFromFile("resources/eat.ogg");

		

		// start play music
		// music_menu.play();
		// music_game.setLoop(true);

		
	}
	catch (std::exception &e) {
			std::cout << e.what() << std::endl;
	}
	// eatBuffer = sf::SoundBuffer();
	// menuBuffer = sf::SoundBuffer();
	eat.setBuffer(eatBuffer);
	menu_sound.setBuffer(menuBuffer);

	eat.play(); //make sound


	std::cout << "SoundSFML::init()" << std::endl;
}

void 	SoundSFML::set_menu(bool b) {
	menu = b;
}

void 	SoundSFML::set_change_sound(bool b) {
	change_sound = b;
}

void 	SoundSFML::set_eat_sound(bool b) {
	eat_sound = b;
}

void 	SoundSFML::set_switch_menu_sound(bool b) {
	switch_menu_sound = b;
}



extern "C" ISound *createSound() {
	return (new SoundSFML());
}


extern "C"	void destroySound(ISound *g) {
	delete g;
}