#include "Player.h"

FPlayer::FPlayer(olc::Sprite* InSprite, FMaze* InMaze) : FBasePawn(InSprite, InMaze)
{
    Position = { 111.0f, 213.0f };
}

void FPlayer::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{

    //TODO: WHILE TURNING, LOCK CONTROLS FOR SAFETY

    
    olc::vf2d NewDirection = Direction;
    olc::vf2d OldDirection = Direction;
    if(Engine->GetKey(olc::Key::UP).bPressed)
    {
        NewDirection = { 0.0f, -1.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::DOWN).bPressed)
    {
        NewDirection = { 0.0f, 1.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::RIGHT).bPressed)
    {
        NewDirection = {1.0f, 0.0f};
        SetDirection(Engine, NewDirection);
    }
    else if (Engine->GetKey(olc::Key::LEFT).bPressed)
    {
        NewDirection = { -1.0f, 0.0f};
        SetDirection(Engine, NewDirection);
    }

    //Adjust to turn if needed
    if(OldDirection != NewDirection && OldDirection.dot(NewDirection) == 0.0f)
    {
        TurnDirection = NewDirection;
        AdjustToTurn();
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
        }
        else
        {
            Move(Engine, ElapsedTime);
        }
    }
    else
    {
        Move(Engine, ElapsedTime);
    }
    DrawSelf(Engine, RoundTime);
}

void FPlayer::AdjustToTurn()
{
    //PacMan advantage while turning
    if(!Maze->GetTile(Position).bIsIntersection)
    {
        bIsTurning = false;
        return;
    }
    
    //Start Turning
    if(!bIsTurning && !Maze->IsPixelACenter(Position)) 
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
