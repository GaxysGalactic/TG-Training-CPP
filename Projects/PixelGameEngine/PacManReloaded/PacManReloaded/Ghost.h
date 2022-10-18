#pragma once
#include "BasePawn.h"
#include "Player.h"

enum class EState
{
    Chase,
    Scatter,
    Frightened,
    Eaten
};

class FGhost : public FBasePawn
{
    olc::Sprite* FrightenedSprite;
    olc::Decal* FrightenedDecal;

    olc::Sprite* EatenSprite;
    olc::Decal* EatenDecal;
    
    olc::vf2d TargetTilePosition = {0.0f, 0.0f};
    olc::vf2d ScatterTilePosition = {0.0f, 0.0f};
    olc::vf2d GhostHousePosition = {110.0f, 117.0f};

    bool bHasTurned = false;

    EState CurrentState = EState::Scatter;
    EState TimerState = EState::Scatter;

    float SecondsInState = 0.0f;
    int SchedulePosition = 0;
    int Level = 1;

    float SecondsSinceFrightened = 0.0f;

    std::vector<float> FirstLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 20.f, 25.f};
    std::vector<float> SecondLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 1033.f, (1.0f/60.0f)};
    std::vector<float> FifthLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 1037.f, (1.0f/60.0f)};

    FPlayer* PacMan;

public:

    FGhost() = default;

    FGhost(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);

    void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;
    
    void SetState(EState NewState);

    void ChangeDirectionToFaceTarget(const olc::PixelGameEngine* Engine);

    void CheckSchedule();

    void Scatter();

    void Chase();

    void Frighten();

    void Die();

    bool CanBeEaten();

    bool IsDead();

    void DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const override;
    
};
