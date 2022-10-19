#include "Blinky.h"

FBlinky::FBlinky(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer) : FGhost(InEngine, InSprite, InMaze, InFrightenedSprite, InEatenSprite, InPlayer)
{
    Position = GhostHousePosition;
    ScatterTilePosition = {203.0f, 4.0f};
    TargetTilePosition  = ScatterTilePosition;
}

void FBlinky::Update(const float ElapsedTime, const float RoundTime)
{
    if(CurrentState == EState::Chase)
    {
        TargetTilePosition = PacMan->GetPosition();
    }
    
    FGhost::Update(ElapsedTime, RoundTime);
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
