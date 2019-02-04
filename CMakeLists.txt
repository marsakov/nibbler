cmake_minimum_required(VERSION 3.13)
project(nibbler)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(nibbler
        inc/Game.hpp
        inc/IGraph.hpp
        inc/Rect.hpp
        inc/Snake.hpp
        src/Game.cpp
        src/main.cpp
        src/Snake.cpp
        libSDL.so
        libSFML.so)

add_library(libSDL.so SHARED src/SDLGraph.cpp)
add_library(libSFML.so SHARED src/SFMLGraph.cpp)
