# Fdf

Snake is a classical game from the 70’s. The simplicity of this addictive game resulted
on its availability on most of existing game platforms under a form or another. For "old"
people, Snake means hours and hours of slacking at school, using the mobile phone version of the Nokia 3310.

Nibbler is yet another snake video game written in C++ including a major twist: dynamic
libraries. Through this project, you will discover the power and usefullness of dynamic
libraries used at runtime. Your goal is splitted in 4 parts : a main executable and 3
dynamic libraries that your main executable will load and use at runtime. Each library
will embed everything your main executable might need to display the game and to get
the player’s inputs. The main executable will only focus on the game logic and interact
with your dynamic libraries. The main executable must interact in a identical way with
any of your libraries.

![Image alt](https://github.com/marsakov/nibbler/raw/master/imgForReadMe/architecture.png)

## The game rules
• The unit of measure is the square.
• The game area is a finite plane of squares. The edges of the plane can’t be passed through.
• The snake starts with a size of 4 squares in the middle of the game area. 
• The snake progresses forward automatically at a constant speed.
• The snake can’t move backwards.
• The snake must be able to turn left or right using the keyboard.
• The goal of this game is to feed your snake to help it grow.
• One food element fills one and only one square of the area.
• When the head of the snake is over a square occupied by food, the food disappears, and one section is added to the tail of the snake on the next move on the same square as the previous last section.
• If the snake hits a wall or one of its own sections, the game is over.
• A scoring system
• A bonus of food appears for a short period of time
• The head section looks different from the others sections
• Sounds 
• Multiplayer ! Two snakes fighting for the same food ! Wicked ! 
• Multiplayer through network. Same as above. 

## Compilation and usage

	git clone https://github.com/marsakov/nibbler.git
	cd nibbler
	make

## Mission Control

#### Menu
	• arrows (up/down):		choose button
	• arrows (left/right):	change speed
	• enter:				select
	• M:					mute
	• 1/2/3:				change library
![Image alt](https://github.com/marsakov/nibbler/raw/master/imgForReadMe//menu.png)

#### Game
	• arrows:				change snake direction
	• escape:				main menu
	• wasd:					change snake direction MULTIPLAYER
	• M:					mute
	• 1/2/3:				change library
	• 4:					change view in 3 library
![Image alt](https://github.com/marsakov/nibbler/raw/master/imgForReadMe//game1.png)

## Run
```
./nibbler 1000 800
```

Run for network:
	Server:
```
./nibbler 1000 800
```
	Client:
```
./nibbler 1000 800 IP-address
```
## Some screenshots
![Image alt](https://github.com/marsakov/nibbler/raw/master/imgForReadMe/game2.png)
![Image alt](https://github.com/marsakov/nibbler/raw/master/imgForReadMe/gameOver.png)
