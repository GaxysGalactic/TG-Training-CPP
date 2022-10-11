#pragma once
#include "olcPixelGameEngine.h"
#include "BasePawn.h"

class FPlayer : public FBasePawn
{
private:

	bool bIsDead = false;

public:

	virtual void Update(olc::PixelGameEngine* Engine, const float ElapsedTime) override;

};