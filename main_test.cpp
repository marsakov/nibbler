#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 200), "SFML works!");
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(10, 100));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}




// clang++ main_test.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib