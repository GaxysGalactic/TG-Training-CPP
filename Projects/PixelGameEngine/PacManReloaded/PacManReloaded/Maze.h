#pragma once
#include "olcPixelGameEngine.h"

class FMaze
{
public:

	struct FTile
	{
		bool bIsObstacle = false;
		bool bHasPellet = false;
		bool bHasEnergizer = false;
		bool bIsIntersection = false;
	};

private:
	olc::Sprite* BackgroundSprite;

	const olc::vf2d BackgroundOffset = { 0.0f, 24.0f };
	const olc::vf2d BackgroundSourcePosition = { 228.0f, 0.0f };
	const olc::vf2d BackgroundSize = { 224.0f, 248.0f };

	const olc::vf2d TileSize = { 8.0f, 8.0f };
	const olc::vf2d TileCenter = { 3.0f, 5.0f };

	const int Columns = 28;
	const int Rows = 36;

	olc::Sprite* TileMap;

	std::vector<FTile> Grid;


public:

	FMaze() = default;

	FMaze(olc::Sprite* InBackground, olc::Sprite* InTileMap);

	~FMaze();

	//virtual void Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime);

	void DrawBase(olc::PixelGameEngine* Engine) const;

	void CreateGrid();

	const FTile& GetTile(const olc::vf2d Position) const;

	FTile& GetTile(const olc::vf2d Position);

	//To check if its at center, its coordinates must be linearly dependant on TileCenter.
	//Shouldn't change direction if Tile in that direction is obstacle.


	//GetNeighbours fills FTiles passed in through input
	//so we can do if(Up)
	//Should probably return pointers to FTiles
	void GetNeighbors(const olc::vf2d Position, FTile* Up, FTile* Down, FTile* Left, FTile* Right);
	
};