#pragma once
#include "olcPixelGameEngine.h"
#include "BasePawn.h"

class FPlayer : public FBasePawn
{
	//Score and Stats
	int Score = 0;
	int ComboMeter = 200;
	
	bool bIsDead = false;
	bool bIsTurning = false;

	bool bHasEnergized = false;
	bool bIsEnergized = false;

	float SecondsSinceEnergized = 0.0f;

	//Turn persistent variables
	olc::vf2d TurnDirection;
	olc::vf2d TurnSource;
	olc::vf2d TurnDestination;
	olc::vf2d TurnDistance;

	//Sprite and Animation
	olc::Sprite* DeathSprite = nullptr;
	olc::Decal* DeathDecal = nullptr;
	float DeathAnimationTimer = 0.0f;

public:

	FPlayer() = default;

	FPlayer(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze, olc::Sprite* InDeathSprite);

	void Update(const float ElapsedTime, const float RoundTime) override;

	void HandleInput(olc::vf2d& OutDirection);

	void AdjustToTurn();

	void EndTurn(const float RoundTime);

	void Die();

	int GetScore() const;

	void SetScore(const int InScore);

	int GetComboMeter() const;

	void SetComboMeter(const int InComboMeter);

	bool IsEnergized() const;

	bool HasEnergized() const;

	void SetIsEnergized(const bool InEnergized);

	void SetHasEnergized(const bool InHasEnergized);

	void DrawSelf(const float RoundTime) const override;

};