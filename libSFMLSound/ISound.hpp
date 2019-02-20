#pragma once

class ISound
{

protected:

	bool menu;
	bool change_sound;
	bool eat_sound;
	bool switch_menu_sound;


public:
	virtual ~ISound() { };

	virtual void	init() = 0;
	virtual void 	Sound() = 0;
	virtual void 	set_menu(bool b) = 0;
	virtual void 	set_change_sound(bool b) = 0;
	virtual void 	set_eat_sound(bool b) = 0;
	virtual void 	set_switch_menu_sound(bool b) = 0;

};
