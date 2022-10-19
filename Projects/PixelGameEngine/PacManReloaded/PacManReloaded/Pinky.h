#pragma once
#include "Ghost.h"

class FPinky : public FGhost
{
public:

    FPinky() = default;

    FPinky(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);

    void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;
    
};
