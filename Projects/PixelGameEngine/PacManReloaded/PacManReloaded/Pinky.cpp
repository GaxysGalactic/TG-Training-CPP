#include "Pinky.h"

FPinky::FPinky(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer) : FGhost(InEngine, InSprite, InMaze, InFrightenedSprite, InEatenSprite, InPlayer)
{
    ScatterTilePosition = {19.0f, 4.0f};
    Position = ScatterTilePosition;
    Position.y += 32.0f;
    TargetTilePosition  = ScatterTilePosition;
}

void FPinky::Update(const float ElapsedTime, const float RoundTime)
{
    if(CurrentState == EState::Chase)
    {
        TargetTilePosition = WrapCoordinates(Engine, PacMan->GetPosition() + PacMan->GetDirection() * 32.0f);
    }
    
    FGhost::Update(ElapsedTime, RoundTime);
}
