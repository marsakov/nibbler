#!/bin/bash
echo "\033[1;35mChecking required libraries...\033[0m"


#SDL
if brew ls --versions sdl2 > /dev/null; then
  echo "\033[1;33mSDL2 is already installed\033[0m"
else
  echo "\033[1;31mSDL2 is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2
  echo "\033[1;32mSDL2 installation completed\033[0m"
fi

if brew ls --versions sdl2_image > /dev/null; then
  echo "\033[1;33mSDL2_Image is already installed\033[0m"
else
  echo "\033[1;31mSDL2_Image is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_image
  echo "\033[1;32mSDL2_Image installation completed\033[0m"
fi

if brew ls --versions sdl2_ttf > /dev/null; then
  echo "\033[1;33mSDL2_TTF is already installed\033[0m"
else
  echo "\033[1;31mSDL2_TTF is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sdl2_ttf
  echo "\033[1;32mSDL2_TTF installation completed\033[0m"
fi


# SFML
if brew ls --versions sfml > /dev/null; then
  echo "\033[1;33mSFML is already installed\033[0m"
else
  echo "\033[1;31mSFML is required in order to start the game. Please wait until it is installed\033[0m"
  brew install sfml
  echo "\033[1;32mSFML installation completed\033[0m"
fi


# OpenGL
if brew ls --versions glew > /dev/null; then
  echo "\033[1;33mGLEW is already installed\033[0m"
else
  echo "\033[1;31mGLEW is required in order to start the game. Please wait until it is installed\033[0m"
  brew install glew
  echo "\033[1;32mSFML installation completed\033[0m"
fi


# libOpenGL         GLUT  OpenGL -lSDL2
## libSDL           -fPIC -lSDL2 -lSDL2_image -lSDL2_ttf
## libSFML         -fPIC -lsfml-graphics -lsfml-window -lsfml-system -rpath
## libSFMLSound     -lsfml-audio -lsfml-system