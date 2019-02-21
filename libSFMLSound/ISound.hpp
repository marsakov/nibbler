#pragma once

class ISound
{

protected:

	bool menu;
	bool change_sound;
	bool eat_sound;
	bool switch_menu_sound;
	bool game_over;
	bool continue_music;


public:
	virtual ~ISound() { };

	virtual void	init() = 0;
	virtual void 	Sound() = 0;
	virtual void 	set_menu(bool b) = 0;
	virtual void 	set_change_sound(bool b) = 0;
	virtual void 	set_eat_sound(bool b) = 0;
	virtual void 	set_switch_menu_sound(bool b) = 0;
	virtual void 	set_game_over(bool b) = 0;
	virtual void 	set_continue_music(bool b)= 0;

};
