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

struct Blocks {
    sf::Sprite sprite;
    Coordinates coord;
    int hitPoints;
    std::string type;

    Blocks(const sf::Sprite& s, Coordinates c, int hp, const std::string& t)
        : sprite(s), coord(c), hitPoints(hp), type(t) {
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
const float paddleSpeed = 800.f;
//------------------------------FUNCTIONS----------------------------------------------------------------------
//_____________________________________________________________________________________________________________
int getHitPointsForType(const std::string& type) {
    if (type == "Glass" || type == "Cracked") return 1;
    if (type == "Static" || type == "Relic") return 2;
    if (type == "Eye") return 3;
    if (type == "cuendillar") return -1; // Indestructible
    return 1; // default fallback
}

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

Blocks blockGenerator(Coordinates coord)
{
    if (isCuendillar()) {
        cuendillar.setPosition(sf::Vector2f(static_cast<float>(coord.x), static_cast<float>(coord.y)));
        return Blocks(cuendillar, coord, -1, "cuendillar");
    }

    {
        
        std::string blckcolor = blockColor[rand() % 7];
        std::string blcktype = blockType[rand() % 5];
        std::string spriteGetter = blckcolor + blcktype;
        sf::Sprite sprite = getSpriteByName(spriteGetter);
        sprite.setPosition(sf::Vector2f(static_cast<float>(coord.x), static_cast<float>(coord.y)));
        int hp = getHitPointsForType(blcktype);

        return Blocks(sprite, coord, hp, blcktype);
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
    sf::Vector2f ballVelocity(400.f, -400.f);


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
            blocks.emplace_back(blockGenerator(coord));
        }
    }



    while (window.isOpen())
    {
        float deltaTime = gameclock.restart().asSeconds();
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

        sf::FloatRect paddleBounds = paddle.getGlobalBounds();

        if (paddleBounds.position.x < 0.f)
        {
            std::cout << paddleBounds.position.y << "\n";
            paddle.setPosition({ 0.f, paddleBounds.position.y });
        }
        if (paddleBounds.position.x + paddleBounds.size.x > window.getSize().x)
        {
            std::cout << paddleBounds.position.y << "\n";
            paddle.setPosition({ (window.getSize().x - paddleBounds.size.x), paddleBounds.position.y });
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

        //------------------Paddle--Ball--COLLISION-------------------------------------------------------------------
        paddleBounds = paddle.getGlobalBounds();
        if (const std::optional intersection = ballBounds.findIntersection(paddleBounds))
        {
            float paddleCenter = paddleBounds.position.x + paddleBounds.size.x / 2.f;
            float ballCenter = ballBounds.position.x + ballBounds.size.x / 2.f;
            float diff = (ballCenter - paddleCenter) / (paddleBounds.size.x / 2.f);
            ballVelocity.x = diff * (paddleSpeed/2);
            ballVelocity.y = -std::abs(ballVelocity.y);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                ballVelocity.x -= (paddleSpeed/4);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                ballVelocity.x += (paddleSpeed/4);
            ball.setPosition(sf::Vector2f{(ball.getPosition().x),(paddleBounds.position.y - ballBounds.size.y)});

            
             
            
        }
        const float maxVelocity = 500.f; // adjust as needed

        if (std::abs(ballVelocity.x) > maxVelocity) {
            ballVelocity.x = (ballVelocity.x > 0 ? 1 : -1) * maxVelocity;
        }
        if (std::abs(ballVelocity.y) > maxVelocity) {
            ballVelocity.y = (ballVelocity.y > 0 ? 1 : -1) * maxVelocity;
        }

        for (auto it = blocks.begin(); it != blocks.end(); ) {
            const sf::FloatRect blockBounds = it->sprite.getGlobalBounds();

            if (const std::optional intersection = ballBounds.findIntersection(blockBounds)) {
                // Calculate centers using position and size (SFML 3.0 style)
                const sf::Vector2f ballCenter = ballBounds.position + ballBounds.size / 2.f;
                const sf::Vector2f blockCenter = blockBounds.position + blockBounds.size / 2.f;
                const sf::Vector2f delta = ballCenter - blockCenter;

                // Determine collision side based on dominant axis
                if (std::abs(delta.x) > std::abs(delta.y)) {
                    ballVelocity.x *= -1.f; // Left or right
                }
                else {
                    ballVelocity.y *= -1.f; // Top or bottom
                }

                // Handle destructible blocks
                if (it->hitPoints > 0) {
                    it->hitPoints--;
                    if (it->hitPoints <= 0) {
                        it = blocks.erase(it);
                        continue; // Skip incrementing
                    }
                }

                break; // Only one block hit per frame
            }

            ++it;
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
