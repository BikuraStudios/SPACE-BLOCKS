#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprites.hpp"
#include <random>
#include <cstdlib>



struct Coordinates
{
    int x;
    int y;
};

std::vector<Coordinates> coordList;

std::string blockType[] = { "Glass","Cracked","Static","Relic","Eye" };
std::string blockColor[] = { "red","orange","yellow","green","blue","indigo","violet" };

int level{ 0 };

bool isCuendillar()
{
    if (level < 10)
    {
        int cuendillarChance = rand() % 101;
        if (cuendillarChance < (level / 10))
            return true;
    }
    else
            return false;
}

sf::Sprite blockGenerator()
{
    bool CuenCheck = isCuendillar();
    if (CuenCheck)
        return cuendillar;
    if (!CuenCheck)
    {
        
        std::string blckcolor;
        std::string blcktype;
        std::string spriteGetter;
        blckcolor = blockColor[rand() % 6];
        blcktype = blockType[rand() % 4];
        spriteGetter = blckcolor + blcktype;
        return getSpriteByName(spriteGetter);
    }
}



void drawBlock(sf::RenderWindow& window, sf::Sprite & sprite, const std::vector<Coordinates>& coords)
{
    for (const Coordinates& i : coords) {
        redGlass.setPosition(sf::Vector2f(static_cast<float>(i.x), static_cast<float>(i.y)));
        window.draw(sprite);
    }
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "NEW PROJECT");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));

    srand(time(0));

    for (int y = 45; y <= 525; y += 30) {
        for (int x = 25; x <= 1810; x += 85) {
            coordList.push_back({ x, y });
        }
    }
    drawBlock(window, blockGenerator(), coordList);


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
        
        
        window.display();
    }
}
