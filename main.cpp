#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprites.hpp"

struct Coordinates
{
    int x;
    int y;
};

std::array<Coordinates, 9> coordList = { { {25,45}, {110,45}, {195,45}, {25,75}, {110,75}, {195,75}, {25,105}, {110,105}, {195,105} } };


void drawBlock(sf::RenderWindow& window, sf::Sprite& redGlass) {
    for (const Coordinates& i : coordList) {
        redGlass.setPosition(sf::Vector2f( static_cast<float>(i.x) ,  static_cast<float>(i.y)) );
        window.draw(redGlass);
    }
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "NEW PROJECT");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));


    



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            if (event->is<sf::Event::Resized>())
            {
                sf::FloatRect viewport;
                sf::Vector2u size = window.getSize();
                auto [windowWidth, windowHeight] = size;
                float aspectRatio = windowWidth / windowHeight;
                float targetRatio{ 16.f / 9.f };


                if (aspectRatio > targetRatio)
                {
                    // Window is too wide — horizontal letterboxing
                    float width = targetRatio / aspectRatio;
                    viewport = sf::FloatRect({ ((1.f - width) / 2.f), 0.f }, { width, 1.f });
                }
                else
                {
                    // Window is too tall — vertical letterboxing
                    float height = aspectRatio / targetRatio;
                    viewport = sf::FloatRect({ 0.f, ((1.f - height) / 2.f) }, { 1.f, height });
                }

                gameView.setViewport(viewport);
            }
        }

        Space_background.setPosition(sf::Vector2f{ 0, 0 });

        
        window.setView(gameView);
        window.clear();
        window.draw(Space_background);
        drawBlock(window, redGlass);
        
        window.display();
    }
}
