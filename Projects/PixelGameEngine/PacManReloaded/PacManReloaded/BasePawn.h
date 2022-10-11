#pragma once
#include "olcPixelGameEngine.h"

class FBasePawn
{
private:

	olc::vf2d Position = { 0.0f, 0.0f };
	olc::vf2d Direction = { 1.0f, 0.0f };
	const float Speed = 5.0f;

	olc::Sprite* BaseSprite = nullptr;
	olc::Decal* BaseDecal = nullptr;


public:

	FBasePawn();

	FBasePawn(olc::Sprite* InSprite);

	~FBasePawn();

	virtual void Update(olc::PixelGameEngine* Engine, const float ElapsedTime);

	void SetDirection(const olc::vf2d& NewDirection);

	void Move(const float ElapsedTime);

	void DrawSelf(olc::PixelGameEngine* Engine);


};