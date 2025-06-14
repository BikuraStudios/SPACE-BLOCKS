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

struct Ball
{

};

struct Blocks 
{
    sf::Sprite sprite;
    Coordinates coord;
    int hitPoints;
    std::string type;
    std::string color;
    float top;
    float bottom;
    float left;
    float right;

    Blocks(const sf::Sprite& s, Coordinates c, int hp, const std::string& t, const std::string& clr, float top, float b, float l, float r)
        : sprite(s), coord(c), hitPoints(hp), type(t), color(clr), top(top), bottom(b), left(l), right(r){
    }
};

struct BallBounds {
    float left;
    float right;
    float top;
    float bottom;
};

BallBounds getBallBounds(const sf::Sprite& ballSprite) {
    const auto bounds = ballSprite.getGlobalBounds(); 

    return BallBounds{
       bounds.position.x,
       bounds.position.x + bounds.size.x,
       bounds.position.y,
       bounds.position.y + bounds.size.y
    };
}
struct BlockBounds {
    float left;
    float right;
    float top;
    float bottom;
};
BlockBounds getBlockBounds(const sf::Sprite& blockSprite) {
    const auto bounds = blockSprite.getGlobalBounds();

    return BlockBounds{
       bounds.position.x,
       bounds.position.x + bounds.size.x,
       bounds.position.y,
       bounds.position.y + bounds.size.y
    };
}

//------------------------------INITIAL VARIABLES---------------------------------------------------------------
//______________________________________________________________________________________________________________


std::vector<Blocks> blocks;

std::vector<Coordinates> coordList;

//std::string blockType[] = { "Glass","Cracked","Static","Relic","Eye" };
std::string blockType[] = { "Glass","Glass","Glass","Glass","Glass" };
std::string blockColor[] = { "red","orange","yellow","green","blue","indigo","violet" };
int RnbwTable[] = { 45,75,105,135,165,195,225,255,285,315,345,375,405,435,465,495,525 };
int level{ 0 };
bool rainbow{ 1 };
bool defaultBallAlive{ 0 };
sf::Clock gameclock;
const float paddleSpeed = 800.f;
sf::Vector2f ballVelocity(00.f, 0.f);
bool ballHolding{ 1 };
sf::Vector2f defaultBallPosition{ 948,980 };

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
        return Blocks(cuendillar, coord, -1, "cuendillar","none",coord.y,(coord.y+30),coord.x,(coord.x+85));
    }

    std::string blckcolor = "red";
    {
        if (rainbow)
        {
            if ((coord.y == 45) || (coord.y == 255) || (coord.y == 465))
            {
                blckcolor = blockColor[0];
            }
            if ((coord.y == 75) || (coord.y == 285) || (coord.y == 495))
            {
                blckcolor = blockColor[1];
            }
            if ((coord.y == 105) || (coord.y == 315) || (coord.y == 525))
            {
                blckcolor = blockColor[2];
            }
            if ((coord.y == 135) || (coord.y == 345))
            {
                blckcolor = blockColor[3];
            }
            if ((coord.y == 195) || (coord.y == 405))
            {
                blckcolor = blockColor[4];
            }
            if ((coord.y == 225) || (coord.y == 435))
            {
                blckcolor = blockColor[5];
            }
            if ((coord.y == 165) || (coord.y == 375))
            {
                blckcolor = blockColor[6];
            }
                
        }
        if (!rainbow)
        {
            blckcolor = blockColor[rand() % 7];
        }
           
        std::string blcktype = blockType[rand() % 5];
        std::string spriteGetter = blckcolor + blcktype;
        //_____________________________________________________________TESTING
        
        //std::cout << "Creating block: " << spriteGetter << " at (" << coord.x << ", " << coord.y << ")\n";
        sf::Sprite sprite = getSpriteByName(spriteGetter);
        //std::cerr << "Block: " << spriteGetter << "placed correctly. \n";
        
        sprite.setPosition(sf::Vector2f(static_cast<float>(coord.x), static_cast<float>(coord.y)));
        int hp = getHitPointsForType(blcktype);

        return Blocks(sprite, coord, hp, blcktype, blckcolor, coord.y, (coord.y + 30), coord.x, (coord.x + 85));
    }
}

void drawBlocks(sf::RenderWindow& window, const std::vector<Blocks>& blocks)
{
    for (const Blocks& block : blocks) {
        window.draw(block.sprite);
    }
}


void ballReset(sf::Sprite& ball, const sf::Sprite& paddle, sf::Vector2f& defaultBallPosition)
{
    std::cout << "Ball Reset \n";
    ballHolding = 1;
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getGlobalBounds();
    ball.setPosition(defaultBallPosition);
    ballVelocity.x = (0.f);
    ballVelocity.y = (0.f);
}

int main()

{
  
    //--------------------------------------BALL AND PADDLE TRANSFORM LOGIC--------------------------------------
  //___________________________________________________________________________________________________________
    sf::Sprite paddle = paddleLarge;
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::Sprite ball = ballDefault;
    //-------------------------------------------------------------------------------------------------------------
      //------------------------------INITIAL SPRITE LOCATIONS-------------------------------------------------------
    sf::Vector2f ballVelocity(0.f, 0.f);


//_____________________________________________________________________________________________________________

    Space_background.setPosition(sf::Vector2f{ 0, 0 });
    paddle.setPosition(sf::Vector2f{ 860,1005 });
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
            sf::FloatRect paddleBounds = paddle.getGlobalBounds();
        float halfPaddle = (paddleBounds.size.x / 2)-12;
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                paddle.move({ -paddleSpeed * deltaTime , 0.f });
                float paddleCenter = paddle.getPosition().x + halfPaddle;
                defaultBallPosition.x = paddleCenter;
                std::cout << paddleCenter << "\n";
                if (ballHolding)
                {
                    ball.move({ -paddleSpeed * deltaTime , 0.f });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                paddle.move({ paddleSpeed * deltaTime , 0.f });
                float paddleCenter = paddle.getPosition().x + halfPaddle;
                defaultBallPosition.x = paddleCenter;
                std::cout << paddleCenter << "\n";
                if (ballHolding)
                {
                    ball.move({ paddleSpeed * deltaTime , 0.f });
                }
            }
            if (!defaultBallAlive)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
                {
                    float paddleCenter = paddle.getPosition().x + halfPaddle;
                    defaultBallPosition.x = paddleCenter;
                    std::cout << paddleCenter << "\n";
                    ballReset(ball,paddle,defaultBallPosition);
                    
                    sf::sleep(sf::milliseconds(5));
                }
            }
             
            if (ballHolding){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    float paddleCenter = paddle.getPosition().x + halfPaddle;
                    defaultBallPosition.x = paddleCenter;
                    std::cout << paddleCenter << "\n";
                    ballVelocity.y = (-400.f);
                    defaultBallAlive = 1;
                    ballHolding = 0;
                }
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
            defaultBallAlive = 0;
            ballVelocity.x = (0);
            ballVelocity.y = (0);
        }

        //------------------Paddle--Ball--COLLISION-------------------------------------------------------------------
        paddleBounds = paddle.getGlobalBounds();
       
        if (const std::optional intersection = ballBounds.findIntersection(paddleBounds)) {
            // Determine which axis had the least overlap (narrow-phase collision resolution)
            float ballLeft = ballBounds.position.x;
            float ballRight = ballBounds.position.x + ballBounds.size.x;
            float ballTop = ballBounds.position.y;
            float ballBottom = ballBounds.position.y + ballBounds.size.y;

            float paddleLeft = paddleBounds.position.x;
            float paddleRight = paddleBounds.position.x + paddleBounds.size.x;
            float paddleTop = paddleBounds.position.y;
            float paddleBottom = paddleBounds.position.y + paddleBounds.size.y;

            float overlapLeft = ballRight - paddleLeft;
            float overlapRight = paddleRight - ballLeft;
            float overlapTop = ballBottom - paddleTop;
            float overlapBottom = paddleBottom - ballTop;

            bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
            bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);

            float minOverlapX = fromLeft ? overlapLeft : overlapRight;
            float minOverlapY = fromTop ? overlapTop : overlapBottom;

            if (minOverlapX < minOverlapY) {
                // Horizontal collision — rare, but possible
                ballVelocity.x *= -1;
            }
            else {
                // Vertical collision — most common, bounce upward
                ballVelocity.y = -std::abs(ballVelocity.y);

                // Add curve based on where the ball hit the paddle
                float paddleCenterX = paddleBounds.position.x + paddleBounds.size.x / 2.f;
                float ballCenterX = ballBounds.position.x + ballBounds.size.x / 2.f;
                float distanceFromCenter = (ballCenterX - paddleCenterX) / (paddleBounds.size.x / 2.f);

                ballVelocity.x = distanceFromCenter * (paddleSpeed);

                // Apply paddle movement influence
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                    ballVelocity.x -= paddleSpeed * 0.25f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                    ballVelocity.x += paddleSpeed * 0.25f;

                // Reposition ball just above paddle to prevent sticking
                if (defaultBallAlive && !ballHolding){
                ball.setPosition(sf::Vector2f{ (ball.getPosition().x),(paddleBounds.position.y - ballBounds.size.y) });
                }
                }
        }
        //________________________________________________________

        const float maxVelocity = 500.f; // adjust as needed

        if (std::abs(ballVelocity.x) > maxVelocity) {
            ballVelocity.x = (ballVelocity.x > 0 ? 1 : -1) * maxVelocity;
        }
        if (std::abs(ballVelocity.y) > maxVelocity) {
            ballVelocity.y = (ballVelocity.y > 0 ? 1 : -1) * maxVelocity;
        }
        sf::Clock gameClock;
       
        for (auto it = blocks.begin(); it != blocks.end(); ) {
            const sf::FloatRect ballRect = ball.getGlobalBounds();
            const sf::FloatRect blockRect = it->sprite.getGlobalBounds();

            // First, check actual collision
            if (ballRect.findIntersection(blockRect)) {
                // Convert to custom bounds (if you need them elsewhere)
                BallBounds ballB = getBallBounds(ball);
                BlockBounds blockB = getBlockBounds(it->sprite);

                // Determine side of impact
                bool fromLeft = std::abs(ballB.right - blockB.left) < std::abs(ballB.left - blockB.right);
                bool fromTop = std::abs(ballB.bottom - blockB.top) < std::abs(ballB.top - blockB.bottom);
                float overlapX = fromLeft ? ballB.right - blockB.left : blockB.right - ballB.left;
                float overlapY = fromTop ? ballB.bottom - blockB.top : blockB.bottom - ballB.top;

                if (overlapX < overlapY) {
                    ballVelocity.x *= -1;
                }
                else {
                    ballVelocity.y *= -1;
                }

                // Handle destructible blocks
                if (it->hitPoints > 0) {
                    it->hitPoints--;
                    if (it->hitPoints <= 0) {
                        it = blocks.erase(it); // remove block and continue
                        break;
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
       if (defaultBallAlive || ballHolding)
       {
        window.draw(ball);
       }
        drawBlocks(window, blocks);
        
        
        window.display();
    }
}
