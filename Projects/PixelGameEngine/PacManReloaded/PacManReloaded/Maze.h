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
	olc::Sprite* FruitSprite = nullptr;
	olc::Sprite* FruitPointsSprite = nullptr;

	olc::Decal* FruitDecal = nullptr;
	olc::Decal* FruitPointsDecal = nullptr;

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

	std::vector<int> Tunnel;
	std::vector<int> ForbiddenZone;

	//Bonus Fruit
	bool bHasFruit = false;
	int BonusFruitCount = 0;
	float FruitTimer = 0.0f;

	bool bDisplayFruitScore = false;
	float ScoreTimer = 0.0f;
	
	const olc::vf2d FruitLocation = {105.f, 156.f};
	const int FruitLocationTileID = 573;
	const olc::vf2d FruitSize = {16.0f, 16.0f};

public:

	FMaze() = default;

	FMaze(olc::PixelGameEngine* InEngine, olc::Sprite* InBackground, olc::Sprite* InTileMap, olc::Sprite* InFruitSprite, olc::Sprite* InFruitPointsSprite);

	void Update(const float ElapsedTime);

	void DrawBase() const;

	void DrawPellets() const;

	void DrawFruit() const;

	void DrawScore() const;

	void CreateGrid();

	void EatPellet(const olc::vf2d& Position);

	int EatFruit();

	bool HasFruit() const;

	const FTile& GetTile(const olc::vf2d& Position) const;

	FTile& GetTile(const olc::vf2d& Position);

	void GetPositionToTileCenter(const olc::vf2d& Position, olc::vf2d& OutPosition) const;

	void GetDirectionFromTileCenter(const olc::vf2d& Position, olc::vf2d& OutDirection) const;
	
	bool IsCenter(const olc::vf2d& Position) const;

	bool IsNextTileObstacle(const olc::vf2d& Position, const olc::vf2d& Direction);

	bool IsTunnel(const olc::vf2d& Position) const;

	bool IsForbiddenZone(const olc::vf2d& Position) const;

	bool IsFruitSpawn(const olc::vf2d& Position) const;
	
	void GetNeighbors(const olc::vf2d& Position, FTile& Up, FTile& Down, FTile& Left, FTile& Right);

	void GetCenterOfTile(const olc::vf2d& Position, olc::vf2d& Center) const;
	
};