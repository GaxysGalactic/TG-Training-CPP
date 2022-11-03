#pragma once
#include "Ghost.h"

class FBlinky : public FGhost
{
    int ChaseThreshold = 20;
    
public:

    FBlinky() = default;

    FBlinky(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);
    
    void Update(const float ElapsedTime, const float RoundTime) override;

    void Chase() override;

    void Scatter() override;
};
