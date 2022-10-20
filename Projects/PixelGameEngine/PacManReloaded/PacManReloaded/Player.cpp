#include "Player.h"

//-------------------------------------------------------------------------------------------
FPlayer::FPlayer(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InDeathSprite) : FBasePawn(InEngine, InSprite, InMaze)
{
    DeathSprite = InDeathSprite;
    DeathDecal = new olc::Decal(DeathSprite);
    Position = { 111.0f, 212.0f };
}

//-------------------------------------------------------------------------------------------
void FPlayer::Update(const float ElapsedTime, const float RoundTime)
{
    //Dead check
    if(bIsDead)
    {
        DeathAnimationTimer += ElapsedTime;
        DrawSelf(RoundTime);
        return;
    }

    //Energize check
    if(bIsEnergized)
    {
        EnergizedTimer += ElapsedTime;

        if(EnergizedTimer >= 7.0f)
        {
            bIsEnergized = false;
            SpeedMultiplier = 0.80f;
            ComboMeter = 200;
        }
    }
    
    olc::vf2d NewDirection = Direction;
    olc::vf2d OldDirection = Direction;

    //Controls
    HandleInput(NewDirection);
    
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
            EndTurn(RoundTime);
            return;
        }
    }

    //Eat Pellets
    if(Maze->GetTile(Position).bHasPellet || Maze->GetTile(Position).bHasEnergizer)
    {
        EatPellets();
    }
    else
    {
        Move(ElapsedTime);
    }
    DrawSelf(RoundTime);
}

//-------------------------------------------------------------------------------------------
void FPlayer::HandleInput(olc::vf2d& OutDirection)
{
    if(Engine->GetKey(olc::Key::UP).bHeld)
    {
        OutDirection = Up;
        SetDirection(OutDirection);
    }
    else if (Engine->GetKey(olc::Key::DOWN).bHeld)
    {
        OutDirection = Down;
        SetDirection(OutDirection);
    }
    else if (Engine->GetKey(olc::Key::RIGHT).bHeld)
    {
        OutDirection = Right;
        SetDirection(OutDirection);
    }
    else if (Engine->GetKey(olc::Key::LEFT).bHeld)
    {
        OutDirection = Left;
        SetDirection(OutDirection);
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::AdjustToTurn()
{
    //PacMan advantage while turning
    if(!Maze->GetTile(Position).bIsIntersection)
    {
        bIsTurning = false;
        return;
    }
    
    //Start Turning
    if(!bIsTurning && !Maze->IsPixelACenter(Position) && !Maze->IsNextTileAnObstacle(Position, TurnDirection)) 
    {
        //Remember Old Position, calculate NewPosition
        TurnSource = Position;

        olc::vf2d PositionFromTileCenter;
        Maze->GetPositionToTileCenter(Position, PositionFromTileCenter);

        const olc::vf2d RotatedPositionFromTileCenter = PositionFromTileCenter.mag() * TurnDirection;

        TurnDistance =  PositionFromTileCenter + RotatedPositionFromTileCenter;
        TurnDestination = TurnSource + TurnDistance;
        
        //Add opposite position vector relative to center
        olc::vf2d DirectionOffset;
        Maze->GetDirectionFromTileCenter(Position, DirectionOffset);
        Direction = TurnDirection + (-1.0f)*DirectionOffset;
        bIsTurning = true;
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::EndTurn(const float RoundTime)
{
    Position = TurnDestination;
    Direction = TurnDirection;
    bIsTurning = false;
    DrawSelf(RoundTime);
}

//-------------------------------------------------------------------------------------------
void FPlayer::EatPellets()
{
    if(Maze->GetTile(Position).bHasPellet)
    {
        Score += 10;
        Maze->EatPellet(Position);
    }
    else
    {
        Score+=50;
        bIsEnergized = true;
        bHasEnergized = true;
        SpeedMultiplier = 0.90f;
        Maze->EatPellet(Position);
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::Die()
{
    Direction = {0.0f, 0.0f};
    bIsDead = true;
}

//-------------------------------------------------------------------------------------------
int FPlayer::GetScore() const
{
    return Score;
}

//-------------------------------------------------------------------------------------------
void FPlayer::SetScore(const int InScore)
{
    Score = InScore;
}

//-------------------------------------------------------------------------------------------
int FPlayer::GetComboMeter() const
{
    return ComboMeter;
}

//-------------------------------------------------------------------------------------------
void FPlayer::SetComboMeter(const int InComboMeter)
{
    ComboMeter = InComboMeter;
}

//-------------------------------------------------------------------------------------------
bool FPlayer::IsEnergized() const
{
    return bIsEnergized;
}

//-------------------------------------------------------------------------------------------
bool FPlayer::HasEnergized() const
{
    return bHasEnergized;
}

//-------------------------------------------------------------------------------------------
void FPlayer::SetIsEnergized(const bool InEnergized)
{
    bIsEnergized = InEnergized;
}

//-------------------------------------------------------------------------------------------
void FPlayer::SetHasEnergized(const bool InHasEnergized)
{
    bHasEnergized = InHasEnergized;
}

//-------------------------------------------------------------------------------------------
void FPlayer::DrawSelf(const float RoundTime) const
{
    if(bIsDead)
    {
        const float OffsetX = floor(DeathAnimationTimer / 0.10f) * 16.0f;

        const olc::vf2d ImageOffset = {OffsetX, 0.0f};
        const olc::vf2d CenterOffset = {7.0f, 8.0f};
        Engine->DrawPartialDecal(Position - CenterOffset, DeathDecal, ImageOffset, Size);
    }
    else
    {
        FBasePawn::DrawSelf(RoundTime);
    }
}
