#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


sf::Texture texture_atlas("atlas.png");
sf::Texture texture_Space("Space.png");
sf::Texture texture_TitleUNCLR("TitleUNCLR.png");
sf::Texture texture_TitleCLR("TitleCLR.png");
sf::Texture texture_logo("logo.png");

sf::Font font("PressStart2P.ttf");

sf::Text startText(font);
sf::Text score(font);
sf::Text lvl(font);
sf::Text lives(font);
sf::Text gmovr(font);
sf::Text nxtlvl(font);
sf::Text pressR(font);



sf::Text remaining(font);

inline sf::Sprite colorTitle{ texture_TitleCLR };
inline sf::Sprite unColorTitle{ texture_TitleUNCLR };
inline sf::Sprite logo{ texture_logo };




// BLOCKS (85 x 30)
inline const sf::IntRect glassRedRect({ 0, 0 }, { 85, 30 });
inline const sf::IntRect crackedRedRect({ 85, 0 }, { 85, 30 });
inline const sf::IntRect staticRedRect({ 170, 0 }, { 85, 30 });
inline const sf::IntRect relicRedRect({ 255, 0 }, { 85, 30 });
inline const sf::IntRect eyeRedRect({ 340, 0 }, { 85, 30 });

inline const sf::IntRect glassOrangeRect({ 0, 30 }, { 85, 30 });
inline const sf::IntRect crackedOrangeRect({ 85, 30 }, { 85, 30 });
inline const sf::IntRect staticOrangeRect({ 170, 30 }, { 85, 30 });
inline const sf::IntRect relicOrangeRect({ 255, 30 }, { 85, 30 });
inline const sf::IntRect eyeOrangeRect({ 340, 30 }, { 85, 30 });

inline const sf::IntRect glassYellowRect({ 0, 60 }, { 85, 30 });
inline const sf::IntRect crackedYellowRect({ 85, 60 }, { 85, 30 });
inline const sf::IntRect staticYellowRect({ 170, 60 }, { 85, 30 });
inline const sf::IntRect relicYellowRect({ 255, 60 }, { 85, 30 });
inline const sf::IntRect eyeYellowRect({ 340, 60 }, { 85, 30 });

inline const sf::IntRect glassGreenRect({ 0, 90 }, { 85, 30 });
inline const sf::IntRect crackedGreenRect({ 85, 90 }, { 85, 30 });
inline const sf::IntRect staticGreenRect({ 170, 90 }, { 85, 30 });
inline const sf::IntRect relicGreenRect({ 255, 90 }, { 85, 30 });
inline const sf::IntRect eyeGreenRect({ 340, 90 }, { 85, 30 });

inline const sf::IntRect glassBlueRect({ 0, 120 }, { 85, 30 });
inline const sf::IntRect crackedBlueRect({ 85, 120 }, { 85, 30 });
inline const sf::IntRect staticBlueRect({ 170, 120 }, { 85, 30 });
inline const sf::IntRect relicBlueRect({ 255, 120 }, { 85, 30 });
inline const sf::IntRect eyeBlueRect({ 340, 120 }, { 85, 30 });

inline const sf::IntRect glassIndigoRect({ 0, 150 }, { 85, 30 });
inline const sf::IntRect crackedIndigoRect({ 85, 150 }, { 85, 30 }); 
inline const sf::IntRect staticIndigoRect({ 170, 150 }, { 85, 30 });
inline const sf::IntRect relicIndigoRect({ 255, 150 }, { 85, 30 });
inline const sf::IntRect eyeIndigoRect({ 340, 150 }, { 85, 30 });

inline const sf::IntRect glassVioletRect({ 0, 180 }, { 85, 30 });
inline const sf::IntRect crackedVioletRect({ 85, 180 }, { 85, 30 }); 
inline const sf::IntRect staticVioletRect({ 170, 180 }, { 85, 30 });
inline const sf::IntRect relicVioletRect({ 255, 180 }, { 85, 30 });
inline const sf::IntRect eyeVioletRect({ 340, 180 }, { 85, 30 });

inline const sf::IntRect cuendillarRect({ 255, 210 }, { 85, 30 }); // unbreakable block

// PADDLES (Various sizes)
inline const sf::IntRect hugePaddleRect({ 50, 260 }, { 300, 25 });
inline const sf::IntRect largePaddleRect({ 0, 210 }, { 200, 25 });
inline const sf::IntRect midPaddleRect({ 0, 235 }, { 100, 25 });
inline const sf::IntRect smallPaddleRect({ 0, 260 }, { 50, 25 });

// BALLS (25 x 25)
inline const sf::IntRect defaultBallRect({ 200, 210 }, { 25, 25 });
inline const sf::IntRect blueBallRect({ 175, 235 }, { 25, 25 });
inline const sf::IntRect redBallRect({ 125, 235 }, { 25, 25 });
inline const sf::IntRect greenBallRect({ 100, 235 }, { 25, 25 });
inline const sf::IntRect yellowBallRect({ 150, 235 }, { 25, 25 });

// MISC
inline const sf::IntRect heartRect({ 225, 210 }, { 25, 25 });
inline const sf::IntRect shipRect({ 348, 210 }, { 74, 65 });
inline const sf::IntRect blastRect({ 200, 235 }, { 19, 25 });

// Sprites (use this after loading texture_atlas)
extern sf::Texture texture_atlas;

inline sf::Sprite redGlass(texture_atlas, glassRedRect);
inline sf::Sprite redCracked(texture_atlas, crackedRedRect);
inline sf::Sprite redStatic(texture_atlas, staticRedRect);
inline sf::Sprite redRelic(texture_atlas, relicRedRect);
inline sf::Sprite redEye(texture_atlas, eyeRedRect);

inline sf::Sprite orangeGlass(texture_atlas, glassOrangeRect);
inline sf::Sprite orangeCracked(texture_atlas, crackedOrangeRect);
inline sf::Sprite orangeStatic(texture_atlas, staticOrangeRect);
inline sf::Sprite orangeRelic(texture_atlas, relicOrangeRect);
inline sf::Sprite orangeEye(texture_atlas, eyeOrangeRect);

inline sf::Sprite yellowGlass(texture_atlas, glassYellowRect);
inline sf::Sprite yellowCracked(texture_atlas, crackedYellowRect);
inline sf::Sprite yellowStatic(texture_atlas, staticYellowRect);
inline sf::Sprite yellowRelic(texture_atlas, relicYellowRect);
inline sf::Sprite yellowEye(texture_atlas, eyeYellowRect);

inline sf::Sprite greenGlass(texture_atlas, glassGreenRect);
inline sf::Sprite greenCracked(texture_atlas, crackedGreenRect);
inline sf::Sprite greenStatic(texture_atlas, staticGreenRect);
inline sf::Sprite greenRelic(texture_atlas, relicGreenRect);
inline sf::Sprite greenEye(texture_atlas, eyeGreenRect);

inline sf::Sprite blueGlass(texture_atlas, glassBlueRect);
inline sf::Sprite blueCracked(texture_atlas, crackedBlueRect);
inline sf::Sprite blueStatic(texture_atlas, staticBlueRect);
inline sf::Sprite blueRelic(texture_atlas, relicBlueRect);
inline sf::Sprite blueEye(texture_atlas, eyeBlueRect);

inline sf::Sprite indigoGlass(texture_atlas, glassIndigoRect);
inline sf::Sprite indigoCracked(texture_atlas, crackedIndigoRect);
inline sf::Sprite indigoStatic(texture_atlas, staticIndigoRect);
inline sf::Sprite indigoRelic(texture_atlas, relicIndigoRect);
inline sf::Sprite indigoEye(texture_atlas, eyeIndigoRect);

inline sf::Sprite violetGlass(texture_atlas, glassVioletRect);
inline sf::Sprite violetCracked(texture_atlas, crackedVioletRect);
inline sf::Sprite violetStatic(texture_atlas, staticVioletRect);
inline sf::Sprite violetRelic(texture_atlas, relicVioletRect);
inline sf::Sprite violetEye(texture_atlas, eyeVioletRect);

inline sf::Sprite cuendillar(texture_atlas, cuendillarRect);

inline sf::Sprite paddleHuge(texture_atlas, hugePaddleRect);
inline sf::Sprite paddleLarge(texture_atlas, largePaddleRect);
inline sf::Sprite paddleMid(texture_atlas, midPaddleRect);
inline sf::Sprite paddleSmall(texture_atlas, smallPaddleRect);
inline sf::Sprite paddle(paddleLarge);

inline sf::Sprite ballDefault(texture_atlas, defaultBallRect);
inline sf::Sprite ballBlue(texture_atlas, blueBallRect);
inline sf::Sprite ballRed(texture_atlas, redBallRect);
inline sf::Sprite ballGreen(texture_atlas, greenBallRect);
inline sf::Sprite ballYellow(texture_atlas, yellowBallRect);
inline sf::Sprite ball(ballDefault);

inline sf::Sprite heart(texture_atlas, heartRect);
inline sf::Sprite heart2(texture_atlas, heartRect);
inline sf::Sprite heart3(texture_atlas, heartRect);

inline sf::Sprite ship(texture_atlas, shipRect);
inline sf::Sprite blast(texture_atlas, blastRect);

inline sf::Sprite Space_background(texture_Space);

//--------------------------------------------------------------------------------

inline sf::Sprite& getSpriteByName(const std::string& name) {
    static const std::unordered_map<std::string, sf::Sprite*> spriteMap = {
        {"redGlass", &redGlass},
        {"redCracked", &redCracked},
        {"redStatic", &redStatic},
        {"redRelic", &redRelic},
        {"redEye", &redEye},

        {"orangeGlass", &orangeGlass},
        {"orangeCracked", &orangeCracked},
        {"orangeStatic", &orangeStatic},
        {"orangeRelic", &orangeRelic},
        {"orangeEye", &orangeEye},

        {"yellowGlass", &yellowGlass},
        {"yellowCracked", &yellowCracked},
        {"yellowStatic", &yellowStatic},
        {"yellowRelic", &yellowRelic},
        {"yellowEye", &yellowEye},

        {"greenGlass", &greenGlass},
        {"greenCracked", &greenCracked},
        {"greenStatic", &greenStatic},
        {"greenRelic", &greenRelic},
        {"greenEye", &greenEye},

        {"blueGlass", &blueGlass},
        {"blueCracked", &blueCracked},
        {"blueStatic", &blueStatic},
        {"blueRelic", &blueRelic},
        {"blueEye", &blueEye},

        {"indigoGlass", &indigoGlass},
        {"indigoCracked", &indigoCracked},
        {"indigoStatic", &indigoStatic},
        {"indigoRelic", &indigoRelic},
        {"indigoEye", &indigoEye},

        {"violetGlass", &violetGlass},
        {"violetCracked", &violetCracked},
        {"violetStatic", &violetStatic},
        {"violetRelic", &violetRelic},
        {"violetEye", &violetEye},

        {"cuendillar", &cuendillar},

        {"paddleHuge", &paddleHuge},
        {"paddleLarge", &paddleLarge},
        {"paddleMid", &paddleMid},
        {"paddleSmall", &paddleSmall},

        {"ballDefault", &ballDefault},
        {"ballBlue", &ballBlue},
        {"ballRed", &ballRed},
        {"ballGreen", &ballGreen},
        {"ballYellow", &ballYellow},

        {"heart", &heart},
        {"ship", &ship},
        {"blast", &blast},

        {"Space_background", &Space_background}
    };

    auto it = spriteMap.find(name);
    if (it != spriteMap.end()) {
        return *(it->second);
    }
    else {
        throw std::runtime_error("Sprite not found: " + name);
    }
}

