#include "Blinky.h"

FBlinky::FBlinky(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer) : FGhost(InSprite, InMaze, InFrightenedSprite, InEatenSprite, InPlayer)
{
    Position = GhostHousePosition;
    ScatterTilePosition = {203.0f, 4.0f};
    TargetTilePosition  = ScatterTilePosition;
}

void FBlinky::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
    if(CurrentState == EState::Chase)
    {
        TargetTilePosition = PacMan->GetPosition();
    }
    
    FGhost::Update(Engine, ElapsedTime, RoundTime);
}

void FBlinky::Chase()
{
    SetState(EState::Chase);
    TargetTilePosition = PacMan->GetPosition();
    SpeedMultiplier = 0.75f;
}

void FBlinky::Scatter()
{
    if(Maze->Pellets <= ChaseThreshold)
    {
        Chase();
    }
    else
    {
        FGhost::Scatter();
    }
}
