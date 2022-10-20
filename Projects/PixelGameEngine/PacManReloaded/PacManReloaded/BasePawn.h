#pragma once
#include "olcPixelGameEngine.h"
#include "Maze.h"

class FBasePawn
{
protected:

	//Other classes
	olc::PixelGameEngine* Engine;
	FMaze* Maze = nullptr;

	//Physics
	olc::vf2d Position = { 111.0f, 213.0f };
	olc::vf2d Direction = { 1.0f, 0.0f };
	const float BaseSpeed = 80.0f;
	const float BaseSpeedFastHack = 2.0f * BaseSpeed;

	bool bIsPaused = false;

	float SpeedMultiplier = 0.80f;

	//Sprites
	const olc::vf2d Size = {16, 16};
	const olc::vf2d CenterOffset = {7.0f, 8.0f};
	olc::Sprite* BaseSprite = nullptr;
	olc::Decal* BaseDecal = nullptr;

	//Useful vectors
	const olc::vf2d Up = {0.0f, -1.0f};
	const olc::vf2d Down = {0.0f, 1.0f};
	const olc::vf2d Left = {-1.0f, 0.0f};
	const olc::vf2d Right = {1.0f, 0.0f};

public:

	FBasePawn() = default;

	FBasePawn(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze);

	virtual ~FBasePawn() = default;

	virtual void Update(const float ElapsedTime, const float RoundTime);

	void SetDirection(const olc::vf2d& NewDirection);

	void Move(const float ElapsedTime);

	virtual void DrawSelf(const float RoundTime) const;

	olc::vf2d& GetPosition();

	olc::vf2d& GetDirection();

	void Pause();

	void UnPause();

	static olc::vf2d WrapCoordinates(const olc::PixelGameEngine* Engine, const olc::vf2d& InVector);
};