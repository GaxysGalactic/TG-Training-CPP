#pragma once
#include "olcPixelGameEngine.h"
#include "BasePawn.h"

class FPlayer : public FBasePawn
{
	int Score = 0;
	
	bool bIsDead = false;
	bool bIsTurning = false;

	bool bEnergized = false;

	olc::vf2d TurnDirection;
	olc::vf2d TurnSource;
	olc::vf2d TurnDestination;
	olc::vf2d TurnDistance;

	olc::Sprite* DeathSprite = nullptr;
	olc::Decal* DeathDecal = nullptr;
	float DeathAnimationTimer = 0.0f;

public:

	FPlayer() = default;

	FPlayer(olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InDeathSprite);

	void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;

	void AdjustToTurn(const olc::PixelGameEngine* Engine);

	void Die();

	int GetScore();

	bool IsEnergized();

	void SetEnergized(const bool InEnergized);

	void DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const override;

};