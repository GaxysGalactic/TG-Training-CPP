#include "Player.h"

FPlayer::FPlayer(olc::Sprite* InSprite, FMaze* InMaze) : FBasePawn(InSprite, InMaze)
{
    Position = { 111.0f, 212.0f };
}

void FPlayer::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
    olc::vf2d NewDirection;

    if(Engine->GetKey(olc::Key::UP).bPressed)
    {
        NewDirection = { 0.0f, -1.0f};
        SetDirection(NewDirection);
    }
    else if (Engine->GetKey(olc::Key::DOWN).bPressed)
    {
        NewDirection = { 0.0f, 1.0f};
        SetDirection(NewDirection);
    }
    else if (Engine->GetKey(olc::Key::RIGHT).bPressed)
    {
        NewDirection = {1.0f, 0.0f};
        SetDirection(NewDirection);
    }
    else if (Engine->GetKey(olc::Key::LEFT).bPressed)
    {
        NewDirection = { -1.0f, 0.0f};
        SetDirection(NewDirection);
    }
    Move(Engine, ElapsedTime);
    DrawSelf(Engine, RoundTime);
}
