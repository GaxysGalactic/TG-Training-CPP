#pragma once
#include "Ghost.h"

class FClyde : public FGhost
{
public:

    FClyde() = default;

    FClyde(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);

    void Update(const float ElapsedTime, const float RoundTime) override;
};
