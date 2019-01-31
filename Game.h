#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <random>
#include <utility>
#include <vector>

enum class Direction {UP, RIGHT, DOWN, LEFT};
enum class MoveEvent {EAT, COLLIDE};

class Game
{
public:
        Game();
     ~Game();

     void run();

private:

     sf::RenderWindow *                   window;
     int                                  score;
     int                                  level;
     bool                                 alive;

     std::pair<int, int>                  foodLocation;

    // Random Number Generation for X
      int                            rangex_from;
      int                            rangex_to;
     std::random_device                   rand_devX;
     std::mt19937                         generatorX;
     std::uniform_int_distribution<int>   distrX;

      int                            rangey_from;
      int                            rangey_to;
     std::random_device                   rand_devY;
     std::mt19937                         generatorY;
     std::uniform_int_distribution<int>   distrY;

     std::vector<std::pair<int, int> >     snake_body;
     Direction                            snake_direction;
     Direction                            new_direction;

     std::pair<int, int>                  getNewFoodLocation();
     void                                 moveSnake();
     void                                 draw();
     bool                                 collides(std::pair<int, int>, std::vector<std::pair<int, int> >);

     sf::Texture tile;
     sf::Texture body;
     sf::Texture food;

     sf::Sprite tile_spr;
     sf::Sprite body_spr;
     sf::Sprite food_spr;
};

#endif