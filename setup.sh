#!/bin/bash
echo "\033[0;33mChecking required libraries...\033[0m"


#SDL
if brew ls --versions sdl2 > /dev/null; then
  echo "\033[0;36mSDL2 is already installed\033[0m"
else
  echo "\033[0;31mSDL2 is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2
  echo "\033[0;32mSDL2 installation completed\033[0m"
fi

if brew ls --versions sdl2_image > /dev/null; then
  echo "\033[0;36mSDL2_Image is already installed\033[0m"
else
  echo "\033[0;31mSDL2_Image is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_image
  echo "\033[0;32mSDL2_Image installation completed\033[0m"
fi

if brew ls --versions sdl2_ttf > /dev/null; then
  echo "\033[0;36mSDL2_TTF is already installed\033[0m"
else
  echo "\033[0;31mSDL2_TTF is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_ttf
  echo "\033[0;32mSDL2_TTF installation completed\033[0m"
fi


# SFML
if brew ls --versions sfml > /dev/null; then
  echo "\033[0;36mSFML is already installed\033[0m"
else
  echo "\033[0;31mSFML is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sfml
  echo "\033[0;32mSFML installation completed\033[0m"
fi


#OpenGL    brew install glfw3
# if brew ls --versions sfml > /dev/null; then
#   echo "\033[0;36mSFML is already installed\033[0m"
# else
#   echo "\033[0;31mSFML is required in order to start the game. Please wait until it is installed\033[0m"
#   brew install sfml
#   echo "\033[0;32mSFML installation completed\033[0m"
# fi




# libOpenGL         GLUT  OpenGL -lSDL2
## libSDL           -fPIC -lSDL2 -lSDL2_image -lSDL2_ttf
## libSFML         -fPIC -lsfml-graphics -lsfml-window -lsfml-system -rpath
## libSFMLSound     -lsfml-audio -lsfml-system