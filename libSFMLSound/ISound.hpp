#pragma once

class ISound
{

protected:

	bool menu;
	bool change_sound;
	bool eat_sound;
	bool switch_menu_sound;
	bool game_over;
	bool new_game;
	bool muteVar;

public:
	virtual ~ISound() { };

	virtual void	init() = 0;
	virtual void 	Sound() = 0;
	virtual void 	set_menu(bool b) = 0;
	virtual void 	set_change_sound(bool b) = 0;
	virtual void 	set_eat_sound(bool b) = 0;
	virtual void 	set_switch_menu_sound(bool b) = 0;
	virtual void 	set_game_over(bool b) = 0;
	virtual void 	set_new_game(bool b) = 0;
	virtual void 	set_mute(bool b) = 0;
	virtual bool 	get_mute() = 0;

};
