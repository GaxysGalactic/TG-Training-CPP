#pragma once
#include "Ghost.h"

class FClyde : public FGhost
{
public:

    FClyde() = default;

    FClyde(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);

    void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;
};
