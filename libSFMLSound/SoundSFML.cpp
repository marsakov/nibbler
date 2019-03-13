#include "SoundSFML.hpp"

SoundSFML::SoundSFML() {
	std::cout << "SoundSFML::SoundSFML()" << std::endl;
	menu = true;
	change_sound = true;
	game_over = false;
	new_game = true;
	muteVar = false;
	init();
}

SoundSFML::~SoundSFML() { }

void 	SoundSFML::Sound() {

	if (eat_sound) {
		eat.play();
		eat_sound = false;
		// std::cout << "eat_sound" << std::endl;
	}
	if (switch_menu_sound) {
		menu_sound.play();
		switch_menu_sound = false;
		// std::cout << "switch_menu_sound" << std::endl;
	}

	if (muteVar) {
		music_menu.setVolume(0.f);
		music_game.setVolume(0.f);
		music_end.setVolume(0.f);
		menu_sound.setVolume(0);
		eat.setVolume(0);
	} else {
		music_menu.setVolume(50.f);
		music_game.setVolume(50.f);
		music_end.setVolume(50.f);
		menu_sound.setVolume(100.f);
		eat.setVolume(100.f);
	}

	if (change_sound) {
		// std::cout << "CHANGE" << std::endl;
		if (menu) {
			if (game_over) {
				music_game.stop();
				music_end.play();
				game_over = false;
				// std::cout << "game over" << std::endl;
				change_sound = true;
			}
			music_game.pause();


			if (music_end.getStatus() == sf::Music::Stopped) {
				music_menu.play();
				change_sound = false;
			}
			music_menu.setLoop(true);
			// std::cout << "menu" << std::endl;
		}
		else {
			music_menu.pause(); 
			if (new_game){
				music_game.stop();
				new_game = false;
			}
			music_game.play(); 
			music_game.setLoop(true);
			// std::cout << "game" << std::endl;

			change_sound = false;

		}
	}

}

void	SoundSFML::init() {

	try {

		// music
		music_menu.openFromFile("resources/menu.ogg");
		music_game.openFromFile("resources/game.ogg");
		music_end.openFromFile("resources/end.ogg");
		//setVolume(50.f)
		music_menu.setVolume(50.f);
		music_game.setVolume(50.f);
		music_end.setVolume(50.f);
		// sound
		menuBuffer.loadFromFile("resources/++.ogg");
		eatBuffer.loadFromFile("resources/eat.ogg");
	}
	catch (std::exception &e) {
			std::cout << e.what() << std::endl;
	}

	eat.setBuffer(eatBuffer);
	menu_sound.setBuffer(menuBuffer);

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

void 	SoundSFML::set_game_over(bool b) {
	game_over = b;
}

void 	SoundSFML::set_new_game(bool b) {
	new_game = b;
}

void 	SoundSFML::set_mute(bool b) {
	muteVar = b;
}

bool 	SoundSFML::get_mute() {
	return muteVar;
}

extern "C" ISound *createSound() {
	return (new SoundSFML());
}


extern "C"	void destroySound(ISound *g) {
	delete g;
}