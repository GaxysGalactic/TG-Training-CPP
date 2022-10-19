#pragma once
#include "olcPixelGameEngine.h"

class FMaze
{
public:

	struct FTile
	{
		int TileID = 0;
		
		bool bIsObstacle = false;
		bool bHasPellet = false;
		bool bHasEnergizer = false;
		bool bIsIntersection = false;
	};

	int Pellets = 244;

private:

	//Engine
	olc::PixelGameEngine* Engine;

	//Sprites
	olc::Sprite* BackgroundSprite = nullptr;
	olc::Sprite* TileMap = nullptr;

	//Background
	const olc::vf2d BackgroundOffset = { 0.0f, 24.0f };
	const olc::vf2d BackgroundSourcePosition = { 0.0f, 0.0f };
	const olc::vf2d BackgroundSize = { 224.0f, 248.0f };

	const olc::Pixel PelletColor = {255, 183, 174};
	
	const olc::vf2d TileSize = { 8.0f, 8.0f };
	const olc::vf2d TileCenter = { 3.0f, 4.0f };

	//Grid
	const int Columns = 28;
	const int Rows = 36;
	
	std::vector<FTile> Grid;


public:

	FMaze() = default;

	FMaze(olc::PixelGameEngine* InEngine, olc::Sprite* InBackground, olc::Sprite* InTileMap);

	void DrawBase() const;

	void DrawPellets() const;

	void CreateGrid();

	void EatPellet(const olc::vf2d& Position);

	const FTile& GetTile(const olc::vf2d& Position) const;

	FTile& GetTile(const olc::vf2d& Position);

	void GetPositionToTileCenter(const olc::vf2d& Position, olc::vf2d& OutPosition) const;

	void GetDirectionFromTileCenter(const olc::vf2d& Position, olc::vf2d& OutDirection) const;
	
	bool IsPixelACenter(const olc::vf2d& Position) const;

	bool IsNextTileAnObstacle(const olc::vf2d& Position, const olc::vf2d& Direction);
	
	void GetNeighbors(const olc::vf2d& Position, FTile& Up, FTile& Down, FTile& Left, FTile& Right);

	void GetCenterOfTile(const olc::vf2d& Position, olc::vf2d& Center) const;
	
};