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

	const FTile& GetTile(const olc::vf2d& Position) const;

	FTile& GetTile(const olc::vf2d& Position);

	void GetPositionFromTileCenter(const olc::vf2d& Position, olc::vf2d& OutPosition) const;

	void GetDirectionToTileCenter(const olc::vf2d& Position, olc::vf2d& OutDirection) const;
	
	bool IsPixelACenter(const olc::vf2d& Position) const;

	bool IsNextTileAnObstacle(const olc::PixelGameEngine* Engine, const olc::vf2d& Position, const olc::vf2d& Direction);
	
	void GetNeighbors(olc::PixelGameEngine* Engine, const olc::vf2d& Position, FTile& Up, FTile& Down, FTile& Left, FTile& Right);

	void GetCenterOfTile(const olc::vf2d& Position, olc::vf2d& Center) const;
	
};