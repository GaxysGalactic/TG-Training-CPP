#pragma once
#include "olcPixelGameEngine.h"
#include "Maze.h"

class FBasePawn
{
protected:
	//Idea: turn this into a position in tile. That way, turns are easier. Or make another position variable.
	//...or make a GridPosition and TilePosition, that way they can be multiplied for TruePosition
	//Tile Position should be distance from center (itself a vf2d, 3,5)
	//A turn would be TilePosition * Direction.
	//Sprite Position would be GridPosition * (TilePosition - Center)
	olc::vf2d Position = { 111.0f, 212.0f };
	olc::vf2d Direction = { 1.0f, 0.0f };
	const float BaseSpeed = 80.0f;

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

	void SetDirection(const olc::vf2d& NewDirection);

	void Move(olc::PixelGameEngine* Engine, const float ElapsedTime);

	void DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const;

	static olc::vf2d WrapCoordinates(olc::PixelGameEngine* Engine, const olc::vf2d& InVector);
};