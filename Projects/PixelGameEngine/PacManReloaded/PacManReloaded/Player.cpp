#include "Player.h"

FPlayer::FPlayer(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InDeathSprite) : FBasePawn(InSprite, InMaze)
{
    DeathSprite = InDeathSprite;
    DeathDecal = new olc::Decal(DeathSprite);
    Position = { 111.0f, 212.0f };
}

void FPlayer::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
    if(bIsDead)
    {
        DeathAnimationTimer += ElapsedTime;
        DrawSelf(Engine, RoundTime);
        return;
    }
    
    olc::vf2d NewDirection = Direction;
    olc::vf2d OldDirection = Direction;
    
    if(Engine->GetKey(olc::Key::UP).bHeld)
    {
        NewDirection = { 0.0f, -1.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::DOWN).bHeld)
    {
        NewDirection = { 0.0f, 1.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::RIGHT).bHeld)
    {
        NewDirection = {1.0f, 0.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::LEFT).bHeld)
    {
        NewDirection = { -1.0f, 0.0f};
        SetDirection(Engine, NewDirection);
    }
    

    //Adjust to turn if needed
    if(OldDirection != NewDirection && OldDirection.dot(NewDirection) == 0.0f)
    {
        TurnDirection = NewDirection;
        AdjustToTurn(Engine);
    }
    
    //EndTurn
    if(bIsTurning)
    {
        olc::vf2d NextPosition = Position + BaseSpeed * SpeedMultiplier * ElapsedTime * Direction;
        if((NextPosition - TurnSource).mag() >= TurnDistance.mag())
        {
            Position = TurnDestination;
            Direction = TurnDirection;
            bIsTurning = false;
            DrawSelf(Engine, RoundTime);
            return;
        }
    }

    //This might cause problems with not eating during turns....apparently not?
    if(Maze->GetTile(Position).bHasPellet || Maze->GetTile(Position).bHasEnergizer)
    {
        if(Maze->GetTile(Position).bHasPellet)
        {
            Score += 10;
            Maze->EatPellet(Engine, Position);
        }
        else
        {
            Score+=50;
            bEnergized = true;
            Maze->EatPellet(Engine, Position);
        }
    }
    else
    {
        Move(Engine, ElapsedTime);
    }
    DrawSelf(Engine, RoundTime);
}

void FPlayer::AdjustToTurn(const olc::PixelGameEngine* Engine)
{
    //PacMan advantage while turning
    if(!Maze->GetTile(Position).bIsIntersection)
    {
        bIsTurning = false;
        return;
    }
    
    //Start Turning
    if(!bIsTurning && !Maze->IsPixelACenter(Position) && !Maze->IsNextTileAnObstacle(Engine, Position, TurnDirection)) 
    {
        //Remember Old Position, calculate NewPosition
        TurnSource = Position;

        olc::vf2d PositionFromTileCenter;
        Maze->GetPositionFromTileCenter(Position, PositionFromTileCenter);

        const olc::vf2d RotatedPositionFromTileCenter = PositionFromTileCenter.mag() * TurnDirection;

        TurnDistance =  PositionFromTileCenter + RotatedPositionFromTileCenter;
        TurnDestination = TurnSource + TurnDistance;
        
        //Add opposite position vector relative to center
        olc::vf2d DirectionOffset;
        Maze->GetDirectionToTileCenter(Position, DirectionOffset);
        Direction = TurnDirection + (-1.0f)*DirectionOffset;
        bIsTurning = true;
    }
}

void FPlayer::Die()
{
    Direction = {0.0f, 0.0f};
    bIsDead = true;
}

int FPlayer::GetScore()
{
    return Score;
}

bool FPlayer::IsEnergized()
{
    return bEnergized;
}

void FPlayer::SetEnergized(const bool InEnergized)
{
    bEnergized = InEnergized;
}

void FPlayer::DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const
{
    if(bIsDead)
    {
        float OffsetX = floor(DeathAnimationTimer / 0.10f) * 16.0f;

        const olc::vf2d ImageOffset = {OffsetX, 0.0f};
        const olc::vf2d CenterOffset = {7.0f, 8.0f};
        Engine->DrawPartialDecal(Position - CenterOffset, DeathDecal, ImageOffset, Size);
    }
    else
    {
        FBasePawn::DrawSelf(Engine, RoundTime);
    }
}
