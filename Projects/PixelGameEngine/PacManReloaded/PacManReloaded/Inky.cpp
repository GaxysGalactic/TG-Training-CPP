#include "Inky.h"

//-------------------------------------------------------------------------------------------
FInky::FInky(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer, FBlinky* InBlinky) : FGhost(InEngine, InSprite, InMaze, InFrightenedSprite, InEatenSprite, InPlayer)
{
    ScatterTilePosition = {219.0f, 284.0f};
    Position = ScatterTilePosition;
    Position.x -= 8.0f;
    Position.y -= 24.0f;
    TargetTilePosition  = ScatterTilePosition;

    Blinky = InBlinky;
}

//-------------------------------------------------------------------------------------------
void FInky::Update(const float ElapsedTime, const float RoundTime)
{
    if(CurrentState == EState::Chase)
    {
        olc::vf2d PacManOffset = PacMan->GetPosition() + PacMan->GetDirection() * 16.0f;

        olc::vf2d DistanceToOffset = PacManOffset - Blinky->GetPosition();

        TargetTilePosition = WrapCoordinates(Engine, PacManOffset + DistanceToOffset);
        
    }
    
    FGhost::Update(ElapsedTime, RoundTime);
}
