#pragma once

#include "ISound.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <dlfcn.h>

class SoundSFML : public ISound
{

sf::SoundBuffer 	menuBuffer, eatBuffer;
sf::Music 			music_menu, music_game, music_end;
sf::Sound 			eat, menu_sound;

protected:

	bool menu;
	bool change_sound;
	bool eat_sound;
	bool switch_menu_sound;
	bool game_over;
	bool new_game;

public:

	SoundSFML();
	virtual ~SoundSFML();

	virtual void	init();
	virtual void 	Sound();
	virtual void 	set_menu(bool b);
	virtual void 	set_change_sound(bool b);
	virtual void 	set_eat_sound(bool b);
	virtual void 	set_switch_menu_sound(bool b);
	virtual void 	set_game_over(bool b);
	virtual void 	set_new_game(bool b);
	
};
