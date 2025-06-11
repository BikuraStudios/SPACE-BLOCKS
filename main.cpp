#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprites.hpp"
#include <random>
#include <cstdlib>

//------------------------------STRUCTURES----------------------------------------------------------------------
//______________________________________________________________________________________________________________

struct Coordinates
{
    int x;
    int y;
};

struct Blocks
{
    sf::Sprite sprite;
    Coordinates coord;

    Blocks(const sf::Sprite& s, Coordinates c)
        : sprite(s), coord(c) {
    }
};

//------------------------------INITIAL VARIABLES---------------------------------------------------------------
//______________________________________________________________________________________________________________


std::vector<Blocks> blocks;

std::vector<Coordinates> coordList;

//std::string blockType[] = { "Glass","Cracked","Static","Relic","Eye" };
std::string blockType[] = { "Glass","Glass","Glass","Glass","Glass" };
std::string blockColor[] = { "red","orange","yellow","green","blue","indigo","violet" };
int level{ 0 };
sf::Clock gameclock;
const float paddleSpeed = 300.f;
//------------------------------FUNCTIONS----------------------------------------------------------------------
//_____________________________________________________________________________________________________________
bool isCuendillar()
{
    //std::cout << "Cuendiar Check!";
    int cuendillarChance{ rand() % 101 };
    std::cout << cuendillarChance <<"\n";
   if (cuendillarChance < (level / 10))
            return true;
   else
            return false;
}

sf::Sprite blockGenerator()
{
    bool CuenCheck = isCuendillar();
    //std::cout << CuenCheck;
    if (CuenCheck)
        return cuendillar;
    if (!CuenCheck)

    {
        
        std::string blckcolor;
        std::string blcktype;
        std::string spriteGetter;
        blckcolor = blockColor[rand() % 7];
        blcktype = blockType[rand() % 5];
        spriteGetter = blckcolor + blcktype;
        return getSpriteByName(spriteGetter);
    }
}

void drawBlocks(sf::RenderWindow& window, const std::vector<Blocks>& blocks)
{
    for (const Blocks& block : blocks) {
        window.draw(block.sprite);
    }
}

int main()

{
  
    //--------------------------------------BALL AND PADDLE TRANSFORM LOGIC--------------------------------------
  //___________________________________________________________________________________________________________
    sf::Sprite ball = ballDefault;
    sf::Sprite paddle = paddleLarge;
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getGlobalBounds();
    //-------------------------------------------------------------------------------------------------------------
      //------------------------------INITIAL SPRITE LOCATIONS-------------------------------------------------------
    sf::Vector2f ballVelocity(50.f, -50.f);


//_____________________________________________________________________________________________________________

    Space_background.setPosition(sf::Vector2f{ 0, 0 });
    paddle.setPosition(sf::Vector2f{ 860,1005 });
    ball.setPosition(sf::Vector2f{ 947,980 });
   // ------------------------------------------------------------------------------------------------------------------




    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "NEW PROJECT");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));

    srand(time(0));

    float deltaTime = gameclock.restart().asSeconds();

    for (int y = 45; y <= 525; y += 30) {
        for (int x = 25; x <= 1810; x += 85) {
            Coordinates coord = { x, y };
            sf::Sprite sprite = blockGenerator();
            sprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
            blocks.emplace_back(std::move(sprite), coord);
        }
    }



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
        
  //------------------------------INITIAL MOVEMENT LOGIC-------------------------------------------------------
  //___________________________________________________________________________________________________________  
        
  
        
  // ----------------------------PADDLES-------------------------------
        if (1)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                paddle.move({-paddleSpeed * deltaTime , 0.f});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                paddle.move({paddleSpeed * deltaTime, 0.f });
            }
        }
        //-----------------------------BALL-----------------------------------
        ball.move(ballVelocity * deltaTime);
        sf::FloatRect ballBounds = ball.getGlobalBounds();

        //------------X--Axis----------------
        if (ballBounds.position.x < 0.f) {
            ballVelocity.x *= -1;
        }
        if (ballBounds.position.x + ballBounds.size.x > window.getSize().x) {
            ballVelocity.x *= -1;
        }

        //------------Y--Axis----------------
        if (ballBounds.position.y < 0.f) {
            ballVelocity.y *= -1;
        }
        if (ballBounds.position.y + ballBounds.size.y > window.getSize().y) {
            ballVelocity.y *= -1;
        }
        
       //------------------------------INITIAL COLLISION AND CLAMP----------------------------------------------------
       //_____________________________________________________________________________________________________________ 
       // ------------------------------------BALL----------------------------------------------------------------------

       //    
        
        
        window.setView(gameView);
        window.clear();
        window.draw(Space_background);
        window.draw(paddle);
        window.draw(ball);
        drawBlocks(window, blocks);
        
        
        window.display();
    }
}
