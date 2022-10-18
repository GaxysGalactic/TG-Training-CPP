#include "Ghost.h"

FGhost::FGhost(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer) : FBasePawn(InSprite, InMaze)
{
    //TODO: Remove these debug ones
    Position = GhostHousePosition;
    TargetTilePosition= { 111.0f, 213.0f };
    ScatterTilePosition = {203.0f, 36.0f};

    FrightenedSprite = InFrightenedSprite;
    EatenSprite = InEatenSprite;

    FrightenedDecal = new olc::Decal(FrightenedSprite);
    EatenDecal = new olc::Decal(EatenSprite);

    PacMan = InPlayer;
}

void FGhost::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
    SecondsInState += ElapsedTime;

    //TODO: TEMPORARY
    if(CurrentState == EState::Chase)
    {
        TargetTilePosition = PacMan->GetPosition();
    }

    if(CurrentState == EState::Frightened)
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

    if(CurrentState == EState::Eaten)
    {
        if(Maze->GetTile(Position).TileID == Maze->GetTile(GhostHousePosition).TileID)
        {
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
    
    CheckSchedule();

    //TODO: Might overshoot tile center...
    
    if(Maze->IsPixelACenter(Position) && Maze->GetTile(Position).bIsIntersection && !bHasTurned)
    {
        ChangeDirectionToFaceTarget(Engine);
        bHasTurned = true;
    }
    else if (!Maze->GetTile(Position).bIsIntersection)
    {
        bHasTurned = false;
    }
    //FBasePawn::Update(Engine, ElapsedTime, RoundTime);
    Move(Engine, ElapsedTime);
    DrawSelf(Engine, RoundTime);
}

void FGhost::SetState(EState NewState)
{
    CurrentState = NewState;
    if(!Maze->GetTile(Position).bIsIntersection)
    {
        Direction *= -1;
    }
}

void FGhost::ChangeDirectionToFaceTarget(const olc::PixelGameEngine* Engine)
{
    olc::vf2d Up = {0.0f, -1.0f};
    olc::vf2d Down = {0.0f, 1.0f};
    olc::vf2d Left = {-1.0f, 0.0f};
    olc::vf2d Right = {1.0f, 0.0f};

    if(CurrentState == EState::Frightened)
    {
        std::vector<olc::vf2d> RandomPool;
        if(!Maze->IsNextTileAnObstacle(Engine, Position, Up))
        {
            RandomPool.push_back(Up);
        }
        if(!Maze->IsNextTileAnObstacle(Engine, Position, Down))
        {
            RandomPool.push_back(Down);
        }
        if(!Maze->IsNextTileAnObstacle(Engine, Position, Left))
        {
            RandomPool.push_back(Left);
        }
        if(!Maze->IsNextTileAnObstacle(Engine, Position, Right))
        {
            RandomPool.push_back(Right);
        }
            
        SetDirection(Engine, RandomPool.at(std::rand() % RandomPool.size()));
    }

    std::pair<float, olc::vf2d> UpPair = {
        Maze->IsNextTileAnObstacle(Engine, Position, Up) ? 999.0f : (TargetTilePosition - (Position + (8 * Up))).mag(),
        Up
    };
    std::pair<float, olc::vf2d> DownPair = {
        Maze->IsNextTileAnObstacle(Engine, Position, Down) ? 999.0f : (TargetTilePosition - (Position + (8 * Down))).mag(),
        Down
    };
    std::pair<float, olc::vf2d> LeftPair = {
        Maze->IsNextTileAnObstacle(Engine, Position, Left) ? 999.0f : (TargetTilePosition - (Position + (8 * Left))).mag(),
        Left
    };
    std::pair<float, olc::vf2d> RightPair = {
        Maze->IsNextTileAnObstacle(Engine, Position, Right) ? 999.0f : (TargetTilePosition - (Position + (8 * Right))).mag(),
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
        SetDirection(Engine, Candidates.front().second);
    }
    else
    {
        SetDirection(Engine, Candidates.at(1).second);
    }
}

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

void FGhost::Scatter()
{
    SetState(EState::Scatter);
    TargetTilePosition = ScatterTilePosition;
    SpeedMultiplier = 0.75f;
}

void FGhost::Chase()
{
    //TODO: this is only temporary while we implement the other ghosts.
    SetState(EState::Chase);
    TargetTilePosition = ScatterTilePosition;
    SpeedMultiplier = 0.75f;
}

void FGhost::Frighten()
{
    SetState(EState::Frightened);
    SpeedMultiplier = 0.50f;
}

void FGhost::Die()
{
    SetState(EState::Eaten);
    TargetTilePosition = GhostHousePosition;
    SpeedMultiplier = 2.0f;
}

bool FGhost::CanBeEaten()
{
    return CurrentState == EState::Frightened;
}

bool FGhost::IsDead()
{
    return CurrentState == EState::Eaten;
}

void FGhost::DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const
{
    if(CurrentState == EState::Frightened)
    {
        float OffsetX = 0.0f;

        //Animation
        //TODO: Blink white based on time
        if(static_cast<int>(floor(12 * RoundTime)) % 2 == 0)
        {
            OffsetX += 16.0f;
        }

        const olc::vf2d ImageOffset = {OffsetX, 0.0f};
        const olc::vf2d CenterOffset = {7.0f, 8.0f};
        Engine->DrawPartialDecal(Position - CenterOffset, FrightenedDecal, ImageOffset, Size);
    }
    else if(CurrentState == EState::Eaten)
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
    else
    {
        FBasePawn::DrawSelf(Engine, RoundTime);
    }
    
}


