#include "Clyde.h"

//-------------------------------------------------------------------------------------------
FClyde::FClyde(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite,
    FPlayer* InPlayer) : FGhost(InEngine, InSprite, InMaze, InFrightenedSprite, InEatenSprite, InPlayer)
{
    ScatterTilePosition = {3.0f, 284.0f};
    Position = ScatterTilePosition;
    Position.x += 8.0f;
    Position.y -= 24.0f;
    TargetTilePosition  = ScatterTilePosition;
}

//-------------------------------------------------------------------------------------------
void FClyde::Update(const float ElapsedTime, const float RoundTime)
{
    if(CurrentState == EState::Chase)
    {
        if((PacMan->GetPosition() - Position).mag() < 8.0f)
        {
            TargetTilePosition = ScatterTilePosition;
        }
        else
        {
            TargetTilePosition = PacMan->GetPosition();
        }
        
    }
    
    FGhost::Update(ElapsedTime, RoundTime);
}
