#include "Ghost.h"
//-------------------------------------------------------------------------------------------
FGhost::FGhost(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer) : FBasePawn(InEngine, InSprite, InMaze)
{
    FrightenedSprite = InFrightenedSprite;
    EatenSprite = InEatenSprite;

    FrightenedDecal = new olc::Decal(FrightenedSprite);
    EatenDecal = new olc::Decal(EatenSprite);

    SpeedMultiplier = 0.75f;

    PacMan = InPlayer;
}

//-------------------------------------------------------------------------------------------
void FGhost::Update(const float ElapsedTime, const float RoundTime)
{
    SecondsInState += ElapsedTime;

    CheckFrightened(ElapsedTime);

    CheckEaten();
    
    CheckSchedule();
    
    CheckTurn();
    
    Move(ElapsedTime);
    DrawSelf(RoundTime);
}

//-------------------------------------------------------------------------------------------
void FGhost::SetState(const EState NewState)
{
    CurrentState = NewState;
    if(!Maze->GetTile(Position).bIsIntersection)
    {
        Direction *= -1;
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::ChangeDirectionToFaceTarget()
{
    if(CurrentState == EState::Frightened)
    {
        ChooseRandomDirection();
    }
    else
    {
        ChooseBestDirection();
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::ChooseRandomDirection()
{
    std::vector<olc::vf2d> RandomPool;
    if(!Maze->IsNextTileAnObstacle(Position, Up))
    {
        RandomPool.push_back(Up);
    }
    if(!Maze->IsNextTileAnObstacle(Position, Down))
    {
        RandomPool.push_back(Down);
    }
    if(!Maze->IsNextTileAnObstacle(Position, Left))
    {
        RandomPool.push_back(Left);
    }
    if(!Maze->IsNextTileAnObstacle(Position, Right))
    {
        RandomPool.push_back(Right);
    }
            
    SetDirection(RandomPool.at(std::rand() % RandomPool.size()));
}

//-------------------------------------------------------------------------------------------
void FGhost::ChooseBestDirection()
{
    std::pair<float, olc::vf2d> UpPair = {
        Maze->IsNextTileAnObstacle(Position, Up) ? 999.0f : (TargetTilePosition - (Position + (8 * Up))).mag(),
        Up
    };
    std::pair<float, olc::vf2d> DownPair = {
        Maze->IsNextTileAnObstacle(Position, Down) ? 999.0f : (TargetTilePosition - (Position + (8 * Down))).mag(),
        Down
    };
    std::pair<float, olc::vf2d> LeftPair = {
        Maze->IsNextTileAnObstacle(Position, Left) ? 999.0f : (TargetTilePosition - (Position + (8 * Left))).mag(),
        Left
    };
    std::pair<float, olc::vf2d> RightPair = {
        Maze->IsNextTileAnObstacle(Position, Right) ? 999.0f : (TargetTilePosition - (Position + (8 * Right))).mag(),
        Right
    };

    std::vector<std::pair<float, olc::vf2d>> Candidates;
    Candidates.push_back(UpPair);
    Candidates.push_back(DownPair);
    Candidates.push_back(LeftPair);
    Candidates.push_back(RightPair);
    
    std::sort(Candidates.begin(), Candidates.end());

    if(Candidates.front().second != Direction * -1)
    {
        SetDirection(Candidates.front().second);
    }
    else
    {
        SetDirection(Candidates.at(1).second);
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::CheckSchedule()
{
    std::vector<float>& CurrentSchedule = FirstLevelSchedule;
    if(Level > 1 && Level < 5)
    {
        CurrentSchedule = SecondLevelSchedule;
    }
    else if(Level > 4)
    {
        CurrentSchedule = FifthLevelSchedule;
    }
    
    if(SecondsInState >= CurrentSchedule.at(SchedulePosition) && SchedulePosition + 1 < CurrentSchedule.size())
    {
        SchedulePosition++;
        SecondsInState = 0.0f;

        if(TimerState == EState::Scatter)
        {
            TimerState = EState::Chase;
            if(CurrentState != EState::Frightened && CurrentState != EState::Eaten)
            {
                Chase();
            }
        }
        else
        {
            TimerState = EState::Scatter;
            if(CurrentState != EState::Frightened && CurrentState != EState::Eaten)
            {
                Scatter();
            }
        }
        
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::CheckFrightened(const float ElapsedTime)
{
    if(CurrentState == EState::Frightened && !bIsPaused)
    {
        SecondsSinceFrightened += ElapsedTime;

        if(SecondsSinceFrightened >= 7.0f)
        {
            if(TimerState == EState::Scatter)
            {
                Scatter();
            }
            else
            {
                Chase();
            }
            SecondsSinceFrightened = 0.0f;
        }
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::CheckEaten()
{
    if(CurrentState == EState::Eaten)
    {
        if(Maze->GetTile(Position).TileID == Maze->GetTile(GhostHousePosition).TileID)
        {
            //TODO: Implement Ghost House here. We could make it so they just teleport first to this and set timer.
            
            if(TimerState == EState::Scatter)
            {
                Scatter();
            }
            else
            {
                Chase();
            }
        }
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::CheckTurn()
{
    if(Maze->IsPixelACenter(Position) && Maze->GetTile(Position).bIsIntersection && !bHasTurned)
    {
        ChangeDirectionToFaceTarget();
        bHasTurned = true;
    }
    else if (!Maze->GetTile(Position).bIsIntersection)
    {
        bHasTurned = false;
    }
}

//-------------------------------------------------------------------------------------------
void FGhost::Scatter()
{
    SetState(EState::Scatter);
    TargetTilePosition = ScatterTilePosition;
    SpeedMultiplier = 0.75f;
}

//-------------------------------------------------------------------------------------------
void FGhost::Chase()
{
    //Default runs away
    SetState(EState::Chase);
    TargetTilePosition = ScatterTilePosition;
    SpeedMultiplier = 0.75f;
}

//-------------------------------------------------------------------------------------------
void FGhost::Frighten()
{
    SetState(EState::Frightened);
    SpeedMultiplier = 0.50f;
}

//-------------------------------------------------------------------------------------------
void FGhost::Die()
{
    SetState(EState::Eaten);
    TargetTilePosition = GhostHousePosition;
    SpeedMultiplier = 1.5f;
}

//-------------------------------------------------------------------------------------------
bool FGhost::CanBeEaten() const
{
    return CurrentState == EState::Frightened;
}

//-------------------------------------------------------------------------------------------
bool FGhost::IsDead() const
{
    return CurrentState == EState::Eaten;
}

//-------------------------------------------------------------------------------------------
void FGhost::DrawSelf(const float RoundTime) const
{
    if(CurrentState == EState::Frightened)
    {
        DrawFrightened(RoundTime);
    }
    else if(CurrentState == EState::Eaten)
    {
        DrawEaten();
    }
    else
    {
        FBasePawn::DrawSelf(RoundTime);
    }
    
}

//-------------------------------------------------------------------------------------------
void FGhost::DrawFrightened(const float RoundTime) const
{
    float OffsetX = 0.0f;
        
    //Animation
    if(SecondsSinceFrightened >= 5.0f)
    {
        if(static_cast<int>(floor(6 * RoundTime)) % 2 == 0)
        {
            OffsetX += 32.0f;
        }
    }
        
    if(static_cast<int>(floor(12 * RoundTime)) % 2 == 0)
    {
        OffsetX += 16.0f;
    }

    const olc::vf2d ImageOffset = {OffsetX, 0.0f};
    const olc::vf2d CenterOffset = {7.0f, 8.0f};
    Engine->DrawPartialDecal(Position - CenterOffset, FrightenedDecal, ImageOffset, Size);
}

//-------------------------------------------------------------------------------------------
void FGhost::DrawEaten() const
{
    float OffsetX = 0.0f;

    if(Direction.x == 1.0f)
    {
        OffsetX = 0.0f;
    }
    else if(Direction.x == -1.0f)
    {
        OffsetX = 16.0f;
    }
    else if(Direction.y == -1.0f)
    {
        OffsetX = 32.0f;
    }
    else if(Direction.y == 1.0f)
    {
        OffsetX = 48.0f;
    }

    const olc::vf2d ImageOffset = {OffsetX, 0.0f};
    const olc::vf2d CenterOffset = {7.0f, 8.0f};
    Engine->DrawPartialDecal(Position - CenterOffset, EatenDecal, ImageOffset, Size);
}


