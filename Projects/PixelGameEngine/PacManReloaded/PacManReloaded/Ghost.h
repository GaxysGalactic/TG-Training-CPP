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
protected:

    //Sprites and Decals
    olc::Sprite* FrightenedSprite;
    olc::Decal* FrightenedDecal;

    olc::Sprite* EatenSprite;
    olc::Decal* EatenDecal;

    //Positions of relevnt things
    olc::vf2d TargetTilePosition = {0.0f, 0.0f};
    olc::vf2d ScatterTilePosition = {0.0f, 0.0f};
    olc::vf2d GhostHousePosition = {110.0f, 116.0f};

    //Turn
    bool bHasTurned = false;

    //State logic
    EState CurrentState = EState::Scatter;
    EState TimerState = EState::Scatter;

    float SecondsInState = 0.0f;
    int SchedulePosition = 0;
    int Level = 1;

    float SecondsSinceFrightened = 0.0f;

    //State Schedule
    std::vector<float> FirstLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 20.f, 25.f};
    std::vector<float> SecondLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 1033.f, (1.0f/60.0f)};
    std::vector<float> FifthLevelSchedule = {7.f, 20.f, 7.f, 20.f, 5.f, 1037.f, (1.0f/60.0f)};

    //Other classes
    FPlayer* PacMan;

public:

    FGhost() = default;

    FGhost(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InFrightenedSprite, olc::Sprite* InEatenSprite, FPlayer* InPlayer);

    virtual void Update(const float ElapsedTime, const float RoundTime) override;
    
    void SetState(EState NewState);

    void ChangeDirectionToFaceTarget();

    void CheckSchedule();

    virtual void Scatter();

    virtual void Chase();

    void Frighten();

    void Die();

    bool CanBeEaten() const;

    bool IsDead() const;

    void DrawSelf(const float RoundTime) const override;
    
};
