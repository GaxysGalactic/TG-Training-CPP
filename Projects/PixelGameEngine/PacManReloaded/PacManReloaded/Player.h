#pragma once
#include "olcPixelGameEngine.h"
#include "BasePawn.h"

class FPlayer : public FBasePawn
{
	bool bIsDead = false;
	bool bIsTurning = false;

	olc::vf2d TurnDirection;
	olc::vf2d TurnSource;
	olc::vf2d TurnDestination;
	olc::vf2d TurnDistance;

public:

	FPlayer() = default;

	FPlayer(olc::Sprite* InSprite, FMaze* InMaze);

	void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;

	void AdjustToTurn(const olc::PixelGameEngine* Engine);

};