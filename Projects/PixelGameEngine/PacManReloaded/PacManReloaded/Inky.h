#pragma once
#include "Blinky.h"
#include "Ghost.h"

class FInky : public FGhost
{

    FBlinky* Blinky;
    
public:

    FInky() = default;

    FInky(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer, FBlinky* InBlinky);

    void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;
    
};
