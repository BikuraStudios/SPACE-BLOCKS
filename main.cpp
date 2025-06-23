#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Sprites.hpp"
#include <random>
#include <cstdlib>

using BlockSpawnRule = bool(*)(int x, int y);


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

std::vector<std::string> levelNames = {
    "Level 1: Initial Contact",
    "Level 2: Pattern Emergence",
    "Level 3: Signal Stabilized",
    "Level 4: Dual Echoes",
    "Level 5: Symmetry Breach",
    "Level 6: Envelope Expansion",
    "Level 7: Upper Containment Zone",
    "Level 8: Lower Containment Zone",
    "Level 9: Phase Oscillation",
    "Level 10: Total Saturation",
    "Level 11: Structural Fracture",
    "Level 12: Substrate Splinter",
    "Level 13: Breach Detected",
    "Level 14: Tectonic Drift",
    "Level 15: Minor Collapse",
    "Level 16: Fault Line",
    "Level 17: Stress Test",
    "Level 18: Shard Bloom",
    "Level 19: Rift Unsealed",
    "Level 20: Fragment Storm",
    "Level 21: Carrier Loss",
    "Level 22: Glitch Bloom",
    "Level 23: Signal Shear",
    "Level 24: Recursive Echo",
    "Level 25: Temporal Jitter",
    "Level 26: Phase Shift",
    "Level 27: Color Bleed",
    "Level 28: Magnetic Interference",
    "Level 29: Null Sweep",
    "Level 30: Spectral Aberration",
    "Level 31: Forgotten Shrine",
    "Level 32: Relic Vault",
    "Level 33: Sacred Resonance",
    "Level 34: Celestial Seal",
    "Level 35: Divinity Matrix",
    "Level 36: Sanctum Breach",
    "Level 37: Broken Halo",
    "Level 38: Angelic Interlock",
    "Level 39: Relic of Descent",
    "Level 40: Halo Interference",
    "Level 41: The Eye Opens",
    "Level 42: Observer Pattern",
    "Level 43: Gaze Returned",
    "Level 44: Witness to Ruin",
    "Level 45: Vision Spiral",
    "Level 46: Echoes of the Watcher",
    "Level 47: Aspect Ratio",
    "Level 48: Watcher’s Breath",
    "Level 49: Nietzschean Lens",
    "Level 50: Mutual Recognition",
    "Level 51: Reverse Containment",
    "Level 52: Anomaly Pulse",
    "Level 53: Breach Halo",
    "Level 54: Sacrificial Loop",
    "Level 55: Color Entropy",
    "Level 56: Memory of Color",
    "Level 57: Outer Spiral",
    "Level 58: Redundancy Collapse",
    "Level 59: Distortion Bloom",
    "Level 60: Ascension Spiral",
    "Level 61: Heat Signature",
    "Level 62: Spherical Reflection",
    "Level 63: Anti-Signal",
    "Level 64: Static Cathedral",
    "Level 65: Peripheral Core",
    "Level 66: Vessel of Doubt",
    "Level 67: Error Translation",
    "Level 68: Intersecting Rituals",
    "Level 69: Mind’s Corridor",
    "Level 70: Filtered Through Flesh",
    "Level 71: Pulse Clot",
    "Level 72: Crystalline Interlock",
    "Level 73: Core Scream",
    "Level 74: Slow Collapse",
    "Level 75: Fracture Path",
    "Level 76: Glass Circuit",
    "Level 77: Last Echo",
    "Level 78: The Watcher Sleeps",
    "Level 79: Symmetry Fails",
    "Level 80: Prism Wept",
    "Level 81: Memory Lock",
    "Level 82: Hollow Geometry",
    "Level 83: Feedback Ritual",
    "Level 84: Phantom Glare",
    "Level 85: Retinal Imprint",
    "Level 86: Subconscious Spill",
    "Level 87: The Gaze Collapses",
    "Level 88: Godwire",
    "Level 89: Phantom Architecture",
    "Level 90: Halo Glitch",
    "Level 91: Dream Repetition",
    "Level 92: Anomaly Implodes",
    "Level 93: Silence Converges",
    "Level 94: Sentience Doubled",
    "Level 95: Memory Eats Itself",
    "Level 96: Recursive Core",
    "Level 97: Blind Bloom",
    "Level 98: Interference Crown",
    "Level 99: Worship from Beyond",
    "Level 100: Terminal Entanglement"
};
std::vector<Blocks> blocks;

std::vector<Coordinates> coordList;

//std::string blockType[] = { "Glass","Cracked","Static","Relic","Eye" };
std::string oneType[] = { "Glass","Glass","Glass","Glass","Glass" };
std::string twoType[] = { "Glass","Glass","Cracked","Cracked","Cracked" };
std::string threeType[] = { "Glass","Glass","Static","Cracked","Cracked" };
std::string fourType[] = { "Glass","Relic","Static","Cracked","Cracked" };
std::string fiveType[] = { "Glass","Relic","Static","Cracked","Eye" };



std::string oneColor[] = { "red","red","red","red","red","red","red" };
std::string twoColors[] = { "red","red","red","red","orange","orange","orange" };
std::string threeColors[] = { "red","red","orange","orange","yellow","yellow","red" };
std::string fourColors[] = { "red","red","orange","yellow","green","orange","yellow" };
std::string fiveColors[] = { "red","orange","yellow","green","blue","yellow","red" };
std::string sixColors[] = { "red","orange","yellow","green","blue","indigo","red" };
std::string blockColor[] = { "red","orange","yellow","green","blue","indigo","violet" };
//std::string blockColor[] = { "red","orange","yellow","violet" };


int RnbwTable[] = { 45,75,105,135,165,195,225,255,285,315,345,375,405,435,465,495,525 };
int level{ 0 };
int superlevel{ 0 };
bool rainbow{ 0 };
bool isStart{ 1 };
bool gameOver{ 0 };
bool defaultBallAlive{ 0 };
bool heartCheck{ 0 };
int heartsLeft{ 3 };
int points{ 0 };
float clearPercent{ 0 };
int blocksRemaining{ -1 };
float blockTotal{ 0 };
float clearedBlocks{ 0 };
std::string strpoints = std::to_string(points);
sf::Clock gameclock;
const float paddleSpeed = 800.f;
sf::Vector2f ballVelocity(00.f, 0.f);
bool ballHolding{ 1 };
sf::Vector2f defaultBallPosition{ 948,980 };
int paddleSize = 3;
bool waitingForLevelStart = false;
sf::Clock levelStartClock;
bool splashScreen{ 0 };
bool titleScreen{ 0 };
bool testing{ 0 };
bool gameboyPlayed{ 0 };
sf::Clock titleClock;
bool titleTimer{ 0 };
bool logodisplay{ 1 };
bool blankAfterLogo = false;
bool BGMstarted{ 0 };



//_________________________________SOUNDS______________________________________________________________________

sf::SoundBuffer Gameboy_Buffer("Gameboy.wav");
inline sf::Sound Gameboy(Gameboy_Buffer);

sf::SoundBuffer logoSound_Buffer("logoSound.wav");
inline sf::Sound logoSound(logoSound_Buffer);

sf::Music BGM("BGM.wav");


//------------------------------LEVEL--GENERATION--------------------------------------------------------------
//_____________________________________________________________________________________________________________
// Level 1: TwoRowsTop - Two dense rows at the very top
bool levelTwoRowsTop(int x, int y) {
    return (y == 45 || y == 75);
}

// Level 2: ThreeRowsTop - Three dense rows at the top
bool levelThreeRowsTop(int x, int y) {
    return (y == 45 || y == 75 || y == 105);
}

// Level 3: FourRowsTop - Four dense rows at the top
bool levelFourRowsTop(int x, int y) {
    return (y == 45 || y == 75 || y == 105 || y == 135);
}

// Level 4: TwoRowsTopTwoRowsBottom - Top 2 and bottom 2 rows
bool levelTwoRowsTopTwoRowsBottom(int x, int y) {
    return (y == 45 || y == 75 || y == 495 || y == 525);
}

// Level 5: ThreeRowsTopThreeRowsBottom - Top 3 and bottom 3 rows
bool levelThreeRowsTopThreeRowsBottom(int x, int y) {
    return (y == 45 || y == 75 || y == 105 || y == 495 || y == 525 || y == 465);
}

// Level 6: FourRowsTopFourRowsBottom - Top 4 and bottom 4 rows
bool levelFourRowsTopFourRowsBottom(int x, int y) {
    return (y == 45 || y == 75 || y == 105 || y == 135 ||
        y == 495 || y == 525 || y == 465 || y == 435);
}

// Level 7: TopHalfField - Top half of the field (first 8 rows)
bool levelTopHalfField(int x, int y) {
    int row = (y - 45) / 30;
    return row < 8;
}

// Level 8: BottomHalfField - Bottom half of the field (last 8 rows)
bool levelBottomHalfField(int x, int y) {
    int row = (y - 45) / 30;
    return row >= 8;
}

// Level 9: EvenRowsFullColumns - All even rows, all columns
bool levelEvenRowsFullColumns(int x, int y) {
    int row = (y - 45) / 30;
    return (row % 2 == 0);
}

// Level 10: FullField - All blocks
bool levelFullField(int x, int y) {
    return true;
}


// Assign rules to levels (repeat as needed)
BlockSpawnRule levelRules[] = {
    levelTwoRowsTop,                // Level 1
    levelThreeRowsTop,              // Level 2
    levelFourRowsTop,               // Level 3
    levelTwoRowsTopTwoRowsBottom,   // Level 4
    levelThreeRowsTopThreeRowsBottom, // Level 5
    levelFourRowsTopFourRowsBottom, // Level 6
    levelTopHalfField,              // Level 7
    levelBottomHalfField,           // Level 8
    levelEvenRowsFullColumns,       // Level 9
    levelFullField                  // Level 10
};



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
    //std::cout << cuendillarChance <<"\n";
   if (cuendillarChance < (superlevel / 10))
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
    
    if (superlevel >= 9) rainbow = true;              // red, orange, yellow, violet

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
        if (level <= 0) {
            blckcolor = oneColor[rand() % 7];
        }
        else if (level == 1) {
            blckcolor = twoColors[rand() % 7];
        }
        else if (level == 3) {
            blckcolor = threeColors[rand() % 7];
        }
        else if (level == 4) {
            blckcolor = fourColors[rand() % 7];
        }
        else if (level == 6) {
            blckcolor = fiveColors[rand() % 7];
        }
        else if (level == 7) {
            blckcolor = sixColors[rand() % 7];
        }
        else {
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
            };
        }
           
        std::string blcktype = "Glass";
        if (superlevel <= 9) {
            blcktype = oneType[rand() % 5];
        }
        else if (superlevel <= 19) {
            blcktype = twoType[rand() % 5];
        }
        else if (superlevel <= 29) {
            blcktype = threeType[rand() % 5];
        }
        else if (superlevel <= 39) {
            blcktype = fourType[rand() % 5];
        }
        else if (superlevel <= 99) {
            blcktype = fiveType[rand() % 5];
        }
        

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

int levelUp(int level) {
    return level + 1;
}

void ballReset(sf::Sprite& ball, const sf::Sprite& paddle, sf::Vector2f& defaultBallPosition)
{
    //std::cout << "Ball Reset \n";
    ballHolding = 1;
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    float halfPaddle = (paddleBounds.size.x / 2) - 12;
    float paddleCenter = paddle.getPosition().x + halfPaddle;
    defaultBallPosition.x = paddleCenter;
    defaultBallPosition.y = 980;
    ball.setPosition(defaultBallPosition);
    ballVelocity.x = (0.f);
    ballVelocity.y = (0.f);
}

void getPaddleSize(int paddleSize) {
    if (paddleSize == 4)
    {
        paddle = paddleHuge;
    }
    if (paddleSize == 3)
    {
        paddle = paddleLarge;
    }
    if (paddleSize == 2)
    {
        paddle = paddleMid;
    }
    if (paddleSize == 1)
    {
        paddle = paddleSmall;
    }

}



int getBlockScoreType(const std::string& blockType) {
    if (blockType == "Glass" || blockType == "Cracked") return 100;
    if (blockType == "Static" || blockType == "Relic") return 200;
    if (blockType == "Eye") return 300;
    if (blockType == "cuendillar") return 1000000; // Indestructible
    return 0; // default fallback
}

int getBlockScoreClr(const std::string& blockColor) {
    if (blockColor == "red") return 50;
    if (blockColor == "orange") return 75;
    if (blockColor == "yellow") return 25;
    if (blockColor == "green") return 50;
    if (blockColor == "blue") return 50;
    if (blockColor == "indigo") return 75;
    if (blockColor == "violet") return 25;


    return 0; // default fallback
}

void generateBlocksForLevel(int level) {
    blocks.clear();
    blockTotal = 0;
    BlockSpawnRule rule = levelRules[level % 10];
    for (int y = 45; y <= 525; y += 30) {
        for (int x = 25; x <= 1810; x += 85) {
            if (rule(x, y)) {
                Coordinates coord = { x, y };
                blocks.emplace_back(blockGenerator(coord));
                blockTotal += 1;
            }
        }
    }
}

void blocksLeft() {
    blocksRemaining = static_cast<int>(std::round(blockTotal * 0.75f));
}

void levelFinished() {
    // Reset ball state only
    ballVelocity = sf::Vector2f(0.f, 0.f);
    ballHolding = true;
    defaultBallAlive = false;

    level = levelUp(level);
    superlevel = levelUp(superlevel);
    if (level > 9) { level = level % 10; }
    if (superlevel >= static_cast<int>(levelNames.size())) {
        superlevel = 0;
    }
    if ((superlevel % 10) == 0) {
        heartsLeft = 3;
    }
    clearedBlocks = 0;
    nxtlvl.setString("LEVEL: " + std::to_string(superlevel + 1));
    pressR.setString("PRESS R TO START");
    // Position ball centered on paddle
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    float paddleCenterX = paddle.getPosition().x + (paddleBounds.size.x / 2.f);
    sf::Vector2f ballResetPos = { paddleCenterX - (ball.getGlobalBounds().size.x / 2.f), paddleBounds.position.y - ball.getGlobalBounds().size.y };
    std::cout << level << "\n";
    ball.setPosition(ballResetPos);
    ballDefault.setPosition(ballResetPos);
    defaultBallPosition = ballResetPos;
    splashScreen = 1;
}

void clearPercentage(float clearedBlocks, float blockTotal) {
    if (blockTotal == 0) {
        clearPercent = 0;
        return;
    }
    clearPercent = clearedBlocks / blockTotal;
    if (blocksRemaining==0 && !splashScreen) {
        levelFinished();
    }
}



int main()

{
    //std::cout << points << "\n";
    //--------------------------------------BALL AND PADDLE TRANSFORM LOGIC--------------------------------------
  //___________________________________________________________________________________________________________
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    sf::Sprite ball = ballDefault;
    //-------------------------------------------------------------------------------------------------------------
      //------------------------------INITIAL SPRITE LOCATIONS-------------------------------------------------------
    sf::Vector2f ballVelocity(0.f, 0.f);
    startText.setCharacterSize(50);
    startText.setPosition(sf::Vector2f(450, 575));
    startText.setFillColor(sf::Color::White);
    startText.setString("PRESS SPACE TO START");

    pressR.setCharacterSize(25);
    pressR.setPosition(sf::Vector2f(725, 600));
    pressR.setFillColor(sf::Color::White);

    gmovr.setCharacterSize(75);
    gmovr.setPosition(sf::Vector2f(625, 500));
    gmovr.setFillColor(sf::Color::White);
    gmovr.setString("GAME OVER");

    nxtlvl.setCharacterSize(75);
    nxtlvl.setPosition(sf::Vector2f(625, 500));
    nxtlvl.setFillColor(sf::Color::White);
    nxtlvl.setString("Level: " + std::to_string(level + 1));

    score.setCharacterSize(25);
    score.setPosition(sf::Vector2f(10, 10));
    score.setFillColor(sf::Color::White);

    remaining.setCharacterSize(25);
    remaining.setPosition(sf::Vector2f(1400, 10));
    remaining.setFillColor(sf::Color::White);
    remaining.setString("ANOMALY BREACH IN " + std::to_string(blocksRemaining));


    lvl.setCharacterSize(25);
    lvl.setPosition(sf::Vector2f(300, 10));
    lvl.setFillColor(sf::Color::White);

    heart.setPosition(sf::Vector2f(1300, 10));
    heart2.setPosition(sf::Vector2f(1331, 10));
    heart3.setPosition(sf::Vector2f(1362, 10));
    //_____________________________________________________________________________________________________________

    Space_background.setPosition(sf::Vector2f{ 0, 0 });
    paddle.setPosition(sf::Vector2f{ (1920 / 2) - (paddleBounds.size.x / 2),1005 });
    ball.setPosition(sf::Vector2f{ 948,980 });
    sf::FloatRect titleBounds = unColorTitle.getGlobalBounds();
    unColorTitle.setPosition(sf::Vector2f((1920 / 2) - (titleBounds.size.x / 2), 0));

    // ------------------------------------------------------------------------------------------------------------------



    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "NEW PROJECT");
    window.setFramerateLimit(144);
    window.setPosition({ -8,0 });
    sf::View gameView(sf::FloatRect({ 0.0f, 0.0f }, { 1920.f, 1080.f }));

    srand(time(0));

    float deltaTime = gameclock.restart().asSeconds();


    generateBlocksForLevel(level);
    blocksLeft();

    

    while (window.isOpen())
    {

        float deltaTime = gameclock.restart().asSeconds();
        remaining.setString("ANOMALY BREACH IN " + std::to_string(blocksRemaining));
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                    if (testing && !titleScreen) {
                        superlevel += 1;
                        level += 1;
                        if (level > 9) level = 0;
                        if (level >= 3) {
                            rainbow = true;
                        }
                        if (level < 3) {
                            rainbow = false;
                        }
                        generateBlocksForLevel(level);
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    if (testing && !titleScreen) {

                        superlevel -= 1;
                        if (level < 0) level = 9;
                        if (level >= 2) {
                            rainbow = true;
                        }
                        if (level < 3) {
                            rainbow = false;
                        }
                        generateBlocksForLevel(level);
                    }
                }
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
            if (!gameOver && !logodisplay && !titleScreen && !BGMstarted) {
                BGM.setLooping(true);
                BGM.play();
                BGMstarted = 1;
            }

            if (titleScreen) {
                if (titleBounds.position.y < 520) {
                    std::cout << titleBounds.position.y << "\n";
                    titleBounds = unColorTitle.getGlobalBounds();
                    unColorTitle.move({ 0.f, (paddleSpeed * deltaTime) / 6 });
                }
            }
            sf::FloatRect paddleBounds = paddle.getGlobalBounds();
            float halfPaddle = (paddle.getGlobalBounds().size.x / 2) - 12;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                paddle.move({ -paddleSpeed * deltaTime , 0.f });
                if (ballHolding) ball.move({ -paddleSpeed * deltaTime , 0.f });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                paddle.move({ paddleSpeed * deltaTime , 0.f });
                if (ballHolding) ball.move({ paddleSpeed * deltaTime , 0.f });
            }
            if (!defaultBallAlive)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
                {
                    float paddleCenter = paddle.getPosition().x + halfPaddle;
                    defaultBallPosition.x = paddleCenter;
                    //std::cout << paddleCenter << "\n";
                    ballReset(ball, paddle, defaultBallPosition);
                    //std::cout << ball.getPosition().x << " , " << ball.getPosition().y << "\n";
                    heartCheck = 0;
                    sf::sleep(sf::milliseconds(500));
                    if (splashScreen) {
                        generateBlocksForLevel(level);
                        blocksLeft();
                        splashScreen = { 0 };
                    }
                }
            }

            if (waitingForLevelStart) {
                if (levelStartClock.getElapsedTime().asMilliseconds() >= 300) {
                    waitingForLevelStart = false;
                }
            }
            else {
                // Launch ball
                if (ballHolding && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    ballVelocity = sf::Vector2f(0.f, -400.f);
                    defaultBallAlive = true;
                    ballHolding = false;
                    isStart = false;
                }

            }

            //sf::FloatRect paddleBounds = paddle.getGlobalBounds();

            if (paddleBounds.position.x < 0.f)
            {
                //std::cout << paddleBounds.position.y << "\n";
                paddle.setPosition({ 0.f, paddleBounds.position.y });
            }
            if (paddleBounds.position.x + paddleBounds.size.x > window.getSize().x)
            {
                //std::cout << paddleBounds.position.y << "\n";
                paddle.setPosition({ (window.getSize().x - paddleBounds.size.x), paddleBounds.position.y });
            }

            //-----------------------------BALL-----------------------------------
            if (defaultBallAlive) {
                ball.move(ballVelocity * deltaTime);
            }
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
                if (!heartCheck) {
                    heartsLeft -= 1;
                    //paddleSize -= 1;
                    //int paddleNow =paddle.getPosition().x;
                    //getPaddleSize(paddleSize);
                    //paddle.setPosition(sf::Vector2f{ (paddleNow) +  (paddleBounds.size.x / 4),1005 });
                    heartCheck = 1;

                }
                if (heartsLeft == 0) {
                    gameOver = 1;
                }
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
                    if (defaultBallAlive && !ballHolding) {
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
                            clearedBlocks += 1;
                            blocksRemaining -= 1;
                            //std::cout << clearedBlocks << " cleared of " << blockTotal << " blocks. \n";
                            //std::cout << "Current clear " << clearPercent << "% | GOAL 75%." << "\n";
                            points += (getBlockScoreType(it->type) + getBlockScoreClr(it->color));
                            it = blocks.erase(it); // remove block and continue
                            break;
                        }
                    }

                    break; // Only one block hit per frame
                }

                ++it;
            }
            score.setString("SCORE: " + std::to_string(points));
            lvl.setString(levelNames[superlevel]);



            //------------------------------INITIAL COLLISION AND CLAMP----------------------------------------------------
            //_____________________________________________________________________________________________________________ 
            // ------------------------------------BALL----------------------------------------------------------------------

            //    
            heart.setPosition(sf::Vector2f(1300, 10));




            window.setView(gameView);
            window.clear();
            window.draw(Space_background);
            if (!gameOver)
            {
                if (blocksRemaining == 0 && !splashScreen) {
                    levelFinished();
                }
                window.draw(paddle);
                if (defaultBallAlive || ballHolding)
                {
                    if (isStart) {
                        window.draw(startText);

                    }
                    if (!waitingForLevelStart && (defaultBallAlive || ballHolding)) {
                        window.draw(ball);
                    }
                }
                drawBlocks(window, blocks);

                if (heartsLeft >= 1) {
                    window.draw(heart);
                }
                if (heartsLeft >= 2) {

                    window.draw(heart2);
                }
                if (heartsLeft >= 3) {
                    window.draw(heart3);
                }
                window.draw(score);
                window.draw(lvl);
                window.draw(remaining);


            }
            if (gameOver) {
                window.draw(gmovr);
            }
            if (splashScreen) {
                window.clear();
                window.draw(Space_background);
                window.draw(nxtlvl);
                window.draw(pressR);
            }

            if (logodisplay) {
                window.clear();
                window.draw(Space_background);

                if (!blankAfterLogo) {
                    logo.setPosition(sf::Vector2f{ 460,40 });
                    window.draw(logo);

                    if (!titleTimer) {
                        titleClock.restart();
                        titleTimer = 1;
                        if (!gameboyPlayed) {
                            logoSound.play();
                            gameboyPlayed = 1;
                        }
                    }
                    // After 5 seconds, switch to blank background
                    if (titleTimer && titleClock.getElapsedTime().asSeconds() > 4.5f) {
                        blankAfterLogo = true;
                        titleClock.restart();
                    }
                }
                else {
                    // Show only background for 1 second
                    if (titleClock.getElapsedTime().asSeconds() > 1.f) {
                        logodisplay = 0;
                        titleTimer = 0;
                        blankAfterLogo = false;
                        gameboyPlayed = 0;
                        titleScreen = 1;
                    }
                }
            }




            if (titleScreen) {
                window.clear();
                window.draw(Space_background);
                window.draw(unColorTitle);
                if (titleBounds.position.y > 519.f)
                {
                    colorTitle.setPosition(sf::Vector2f{ titleBounds.position.x, 520.f });
                    window.draw(colorTitle);
                    if (!gameboyPlayed) {
                        Gameboy.play();
                        gameboyPlayed = 1;
                        titleClock.restart();
                        titleTimer = 1;

                    }
                }


                if (gameboyPlayed && titleClock.getElapsedTime().asSeconds() > 2.f) {
                    titleScreen = 0;
                    titleTimer = 0;
                }


                
            }
            window.display();
        }
    }
}