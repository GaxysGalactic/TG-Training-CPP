#pragma once
#include "olcPixelGameEngine.h"
#include "Maze.h"

class FBasePawn
{
protected:
	olc::vf2d Position = { 111.0f, 213.0f };
	olc::vf2d Direction = { 1.0f, 0.0f };
	const float BaseSpeed = 80.0f;
	const float BaseSpeedFastHack = 2.0f * BaseSpeed;

	float SpeedMultiplier = 0.80f;

	const olc::vf2d Size = {16, 16};
	olc::Sprite* BaseSprite = nullptr;
	olc::Decal* BaseDecal = nullptr;

	FMaze* Maze = nullptr;


public:

	FBasePawn() = default;

	FBasePawn(olc::Sprite* InSprite, FMaze* InMaze);

	~FBasePawn();

	virtual void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime);

	void SetDirection(const olc::PixelGameEngine* Engine, const olc::vf2d& NewDirection);

	void Move(const olc::PixelGameEngine* Engine, const float ElapsedTime);

	virtual void DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const;

	olc::vf2d& GetPosition();

	static olc::vf2d WrapCoordinates(const olc::PixelGameEngine* Engine, const olc::vf2d& InVector);
};