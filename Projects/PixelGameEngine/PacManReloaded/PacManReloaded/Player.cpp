#include "Player.h"

//-------------------------------------------------------------------------------------------
FPlayer::FPlayer(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InDeathSprite,
                 olc::Sprite* InGhostPointsSprite) : FBasePawn(InEngine, InSprite, InMaze)
{
    DeathSprite = InDeathSprite;
    DeathDecal = new olc::Decal(DeathSprite);

    GhostPointsSprite = InGhostPointsSprite;
    GhostPointsDecal = new olc::Decal(GhostPointsSprite);

    //Pacman spawn point
    Position = { 111.0f, 212.0f };

    //Pacman isn't affected by the tunnel
    TunnelMultiplier = 1.0f;
}

//-------------------------------------------------------------------------------------------
FPlayer::~FPlayer()
{
    delete DeathDecal;
    delete GhostPointsDecal;
}

//-------------------------------------------------------------------------------------------
void FPlayer::Update(const float ElapsedTime, const float RoundTime)
{
    //Pause check (if was paused on a timer)
    if(bIsPaused && bIsTimerPaused && !bIsEnginePaused)
    {
        UpdatePause(ElapsedTime);
    }
    
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
        UpdateEnergized(ElapsedTime);
    }
    
    //Store New Direction and Old Direction for turns
    olc::vf2d NewDirection = Direction;
    olc::vf2d OldDirection = Direction;

    //Controls
    if(!bIsTurning)
    {
        HandleInput(NewDirection);
    }
    
    //Adjust to turn if needed
    if(OldDirection != NewDirection && OldDirection.dot(NewDirection) == 0.0f)
    {
        TurnDirection = NewDirection;
        AdjustToTurn();
    }
    
    //EndTurn if needed
    if(bIsTurning)
    {
        olc::vf2d NextPosition = Position + BaseSpeed * SpeedMultiplier * ElapsedTime * Direction;
        //Teleport to destination if close enough
        if((NextPosition - TurnSource).mag() >= TurnDistance.mag()
            || TurnDistance.mag() < 1.5f)
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

    //Eat Fruit
    if(Maze->HasFruit() && Maze->IsFruitSpawn(Position))
    {
        Score += Maze->EatFruit();
    }
    
    Move(ElapsedTime);
    DrawSelf(RoundTime);
}

//-------------------------------------------------------------------------------------------
void FPlayer::UpdatePause(const float ElapsedTime)
{
    //Updates pause timer and unpauses if it exceeds limit
    PausedTimer += ElapsedTime;
    if(PausedTimer >= PausedTimerLimit)
    {
        bIsTimerPaused = false;
        PausedTimer = 0.0f;
        PausedTimerLimit = 0.0f;
        UnPause();
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::UpdateEnergized(const float ElapsedTime)
{
    //Updates energized timer and resets if needed
    EnergizedTimer += ElapsedTime;

    if(EnergizedTimer >= 7.0f)
    {
        bIsEnergized = false;
        SpeedMultiplier = 0.80f;
        ComboMeter = 200;
    }
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
    if(!bIsTurning && !Maze->IsCenter(Position) && !Maze->IsNextTileObstacle(Position, TurnDirection)) 
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
        //Pause for "one frame"
        Pause(1.0f/60.0f); 
    }
    else
    {
        Score+=50;
        bIsEnergized = true;
        ComboMeter = 200;
        bHasEnergized = true;
        SpeedMultiplier = 0.90f;
        Maze->EatPellet(Position);
        //Pause for "three frames"
        Pause(3.0f/60.0f); 
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::Die()
{
    Direction = {0.0f, 0.0f};
    bIsDead = true;
}

//-------------------------------------------------------------------------------------------
void FPlayer::Pause()
{
    //Was paused by the engine or through its default instead of on a timer
    bIsEnginePaused = true;
    FBasePawn::Pause();
}

//-------------------------------------------------------------------------------------------
void FPlayer::Pause(const float Seconds)
{
    //Pause for Seconds # of seconds
    bIsPaused = true;
    bIsTimerPaused = true;
    PausedTimerLimit = Seconds;
}

//-------------------------------------------------------------------------------------------
void FPlayer::UnPause()
{
    //A default unpause will override all pause statuses
    bIsTimerPaused = false;
    bIsEnginePaused = false;
    FBasePawn::UnPause();
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
        DrawDeathAnimation();
    }
    else if(Maze->IsNextTileObstacle(Position, Direction))
    {
        DrawIdleAnimation();
    }
    else if(bIsPaused && bIsEnginePaused)
    {
        DrawPoints();
    }
    else
    {
        FBasePawn::DrawSelf(RoundTime);
    }
}

//-------------------------------------------------------------------------------------------
void FPlayer::DrawDeathAnimation() const
{
    const float OffsetX = floor(DeathAnimationTimer / 0.10f) * 16.0f;

    const olc::vf2d ImageOffset = {OffsetX, 0.0f};
    Engine->DrawPartialDecal(Position - CenterOffset, DeathDecal, ImageOffset, Size);
}

//-------------------------------------------------------------------------------------------
void FPlayer::DrawIdleAnimation() const
{
    float OffsetX = 0.0f;

    if(Direction.x == 1.0f)
    {
        OffsetX = 0.0f;
    }
    else if(Direction.x == -1.0f)
    {
        OffsetX = 32.0f;
    }
    else if(Direction.y == -1.0f)
    {
        OffsetX = 64.0f;
    }
    else if(Direction.y == 1.0f)
    {
        OffsetX = 96.0f;
    }

    OffsetX += 16.0f;

    const olc::vf2d ImageOffset = {OffsetX, 0.0f};
    Engine->DrawPartialDecal(Position - CenterOffset, BaseDecal, ImageOffset, Size);
}

//-------------------------------------------------------------------------------------------
void FPlayer::DrawPoints() const
{
    int Power = log2(ComboMeter / 200);
    --Power;

    float OffsetX = 16.0f * Power;
    const olc::vf2d ImageOffset = {OffsetX, 0.0f};
    Engine->DrawPartialDecal(Position - CenterOffset, GhostPointsDecal, ImageOffset, Size);
}
