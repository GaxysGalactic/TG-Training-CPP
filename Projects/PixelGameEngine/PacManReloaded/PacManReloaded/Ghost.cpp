#include "Ghost.h"

FGhost::FGhost(olc::Sprite* InSprite, FMaze* InMaze) : FBasePawn(InSprite, InMaze)
{
    //TODO: Remove these debug ones
    Position += {1.0f, 0.0f};
    TargetTilePosition= { 111.0f, 213.0f };
    ScatterTilePosition = {203.0f, 36.0f};
}

void FGhost::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
    SecondsInState += ElapsedTime;
    CheckSchedule();

    //TODO: Careful! He might not get exactly to center. Have to check if his next move passes the center.
    std::cout << Position << std::endl;

    //Do a breakpoint when he reaches the trouble tile - make a custom if condition
    
    if(Maze->IsPixelACenter(Position) && Maze->GetTile(Position).bIsIntersection)
    {
        ChangeDirectionToFaceTarget(Engine);
    }
    //FBasePawn::Update(Engine, ElapsedTime, RoundTime);
    Move(Engine, ElapsedTime);
    DrawSelf(Engine, RoundTime);
}

void FGhost::SetState(EState NewState)
{
    CurrentState = NewState;
    Direction *= -1;
}

void FGhost::ChangeDirectionToFaceTarget(const olc::PixelGameEngine* Engine)
{
    olc::vf2d Up = {0.0f, -1.0f};
    olc::vf2d Down = {0.0f, 1.0f};
    olc::vf2d Left = {-1.0f, 0.0f};
    olc::vf2d Right = {1.0f, 0.0f};

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

    if(Candidates.front().second != Direction)
    {
        SetDirection(Engine, Candidates.front().second);
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
    
    if(SecondsInState >= CurrentSchedule.at(SchedulePosition) && SchedulePosition < CurrentSchedule.size())
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
}

void FGhost::Chase()
{
    //TODO: this is only temporary while we implement the other ghosts.
    SetState(EState::Chase);
    TargetTilePosition = ScatterTilePosition;
}
