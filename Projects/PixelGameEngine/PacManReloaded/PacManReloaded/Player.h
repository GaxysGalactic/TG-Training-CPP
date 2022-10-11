#pragma once
#include "olcPixelGameEngine.h"
#include "BasePawn.h"

class FPlayer : public FBasePawn
{
	bool bIsDead = false;

public:

	FPlayer() = default;

	FPlayer(olc::Sprite* InSprite);

	void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime) override;

};