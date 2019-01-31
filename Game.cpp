#include "Game.h"

#include <iostream>

// Initialization of static variables

// sf::RenderWindow * Game::window = new sf::RenderWindow(sf::VideoMode(1600, 1600), "Snake", sf::Style::Titlebar | sf::Style::Close);
// int Game::score = 0;
// int Game::level = 1;
// bool Game::alive = true;

// const int Game::rangex_from =    0;
// const int Game::rangex_to =     100;
// const int Game::rangey_from =    0;
// const int Game::rangey_to =     100;

// std::random_device      Game::rand_devX;
// std::random_device      Game::rand_devY;

// std::mt19937            Game::generatorX(Game::rand_devX());
// std::mt19937            Game::generatorY(Game::rand_devY());

// std::uniform_int_distribution<int>   Game::distrX(Game::rangex_from, Game::rangex_to);
// std::uniform_int_distribution<int>   Game::distrY(Game::rangey_from, Game::rangey_to);

// std::vector<std::pair<int, int> >                    Game::snake_body;
// Direction                                           Game::snake_direction;
// Direction                                           Game::new_direction;
// std::pair<int, int>                                 Game::foodLocation = Game::getNewFoodLocation();

// sf::Texture                                         Game::body;
// sf::Texture                                         Game::tile;
// sf::Texture                                         Game::food;
// sf::Sprite                                          Game::body_spr;
// sf::Sprite                                          Game::tile_spr;
// sf::Sprite                                          Game::food_spr;


std::pair<int, int> Game::getNewFoodLocation()
{
    std::pair<int, int> temporalLocation;

    do
    {
        temporalLocation = std::pair<int, int>(Game::distrX(Game::generatorX), Game::distrY(Game::generatorY));
    } while (collides(temporalLocation, Game::snake_body));

    return temporalLocation;
}

bool Game::collides(std::pair<int, int> coordinate, std::vector<std::pair<int, int> > body)
{
    for (int i = 0; i < body.size(); i++)
        if (coordinate.first == body[i].first && coordinate.second == body[i].second)
            return true;

    return false;
}

void Game::moveSnake()
{
    std::pair<int, int> new_head_pos;

    // Calculates the new position the snakes head will take
    switch (new_direction)
    {
    case Direction::UP:
        if (snake_body[0].second - 1 >= rangey_from)
            new_head_pos.second = snake_body[0].second - 1;
        else
            new_head_pos.second = rangey_to;
        new_head_pos.first = snake_body[0].first;       
        break;

    case Direction::DOWN:
        if (snake_body[0].second + 1 <= rangey_to)
            new_head_pos.second = snake_body[0].second + 1;
        else
            new_head_pos.second = rangey_from;
        new_head_pos.first = snake_body[0].first;       
        break;

    case Direction::LEFT:
        if (snake_body[0].first - 1 >= rangex_from)
            new_head_pos.first = snake_body[0].first - 1;
        else
            new_head_pos.first = rangex_to;
        new_head_pos.second = snake_body[0].second;
        break;

    case Direction::RIGHT:
        if (snake_body[0].first + 1 <= rangex_to)
            new_head_pos.first = snake_body[0].first + 1;
        else
            new_head_pos.first = rangex_from;
        new_head_pos.second = snake_body[0].second;
        break;
    }

    //Fast hack <_<
    std::vector<std::pair<int, int> > body_minus_tail = snake_body;
    body_minus_tail.pop_back();

    // Checks if the snake will collide with its own body
    if(collides(new_head_pos, body_minus_tail))
    { 
        std::cout << "You Lost!     Score: " << score << std::endl;
        alive = false;
    }

    if(new_head_pos == foodLocation)
    { 
        score++;
        snake_body.insert(snake_body.begin(), new_head_pos);
        foodLocation = getNewFoodLocation();
    }
    else
    {
        snake_body.insert(snake_body.begin(), new_head_pos);
        snake_body.pop_back();
    }
    snake_direction = new_direction;
}

Game::Game() {

    window = new sf::RenderWindow(sf::VideoMode(1600, 1600), "Snake", sf::Style::Titlebar | sf::Style::Close);
score = 0;
level = 1;
 alive = true;

rangex_from =    0;
rangex_to =     100;
rangey_from =    0;
rangey_to =     100;
}
Game::~Game(){}

void Game::run()
{
    window->setFramerateLimit(60);

    snake_body.push_back(std::pair<int, int>(2, 0));
    snake_body.push_back(std::pair<int, int>(1, 0));
    snake_body.push_back(std::pair<int, int>(0, 0));

    snake_direction = Direction::RIGHT;
    new_direction   = Direction::RIGHT;

    body.loadFromFile("body.png");
    tile.loadFromFile("tile.png");
    food.loadFromFile("food.png");

   

    body_spr.setTexture(body);
    tile_spr.setTexture(tile);
    food_spr.setTexture(food);

    // body_spr.setScale(0.05, 0.05);
    // food_spr.setScale(0.05, 0.05); 

    sf::Clock clock;
    sf::Time time1;

    while (window->isOpen())

    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                // Calculates the new direction the snake is heading based on user input
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    if (snake_direction != Direction::DOWN)
                        new_direction = Direction::UP;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    if (snake_direction != Direction::LEFT)
                        new_direction = Direction::RIGHT;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    if (snake_direction != Direction::UP)
                        new_direction = Direction::DOWN;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    if (snake_direction != Direction::RIGHT)
                        new_direction = Direction::LEFT;
                    break;
                }
                break;

            case sf::Event::Closed:
                window->close();
                break;
            }

        }

        time1 = clock.getElapsedTime();
        if (time1.asMilliseconds() >= 1000/20)
        {
            moveSnake();
            clock.restart();
        }

        if (!alive)
            window->close();

        window->clear();
        draw();
        window->display();

    }
}

void::Game::draw()
{
    for (int i = 0; i < rangex_to; i++)
        for (int j = 0; j < rangey_to; j++)
        {
            tile_spr.setPosition(i*16, j*16);
            window->draw(tile_spr);
        }

    food_spr.setPosition(foodLocation.first*16, foodLocation.second*16);
    window->draw(food_spr);

    for (int i = 0; i < snake_body.size(); i++)
    {
        body_spr.setPosition(snake_body[i].first*16, snake_body[i].second*16);
        window->draw(body_spr);
    }
}