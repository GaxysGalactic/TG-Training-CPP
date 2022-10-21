#include "Maze.h"

#include "BasePawn.h"

//-------------------------------------------------------------------------------------------
FMaze::FMaze(olc::PixelGameEngine* InEngine, olc::Sprite* InBackground, olc::Sprite* InTileMap, olc::Sprite* InFruitSprite, olc::Sprite* InFruitPointsSprite)
{
	Engine = InEngine;
	BackgroundSprite = InBackground;
	FruitSprite = InFruitSprite;
	FruitDecal = new olc::Decal(FruitSprite);
	FruitPointsSprite = InFruitPointsSprite;
	FruitPointsDecal = new olc::Decal(FruitPointsSprite);
	TileMap = InTileMap;
	CreateGrid();

	Tunnel = {476, 477, 478, 479, 480, 481, 498, 499, 501, 502, 503, 504};
	ForbiddenZone = {404, 407, 712, 715};
}

//-------------------------------------------------------------------------------------------
void FMaze::Update(const float ElapsedTime)
{
	if(Pellets == 174 || Pellets == 74)
	{
		//Spawn Bonus Fruit
		bHasFruit = true;
	}
	
	if(bHasFruit)
	{
		FruitTimer += ElapsedTime;

		if(FruitTimer >= 9.0f)
		{
			bHasFruit = false;
			FruitTimer = 0.0f;
			++BonusFruitCount;
		}
		DrawFruit();
	}
	else if (bDisplayFruitScore)
	{
		ScoreTimer += ElapsedTime;
		if(ScoreTimer >= 1.5f)
		{
			bDisplayFruitScore = false;
			ScoreTimer = 0.0f;
		}
		DrawScore();
	}
}

//-------------------------------------------------------------------------------------------
void FMaze::DrawBase() const
{
	Engine->DrawPartialSprite(BackgroundOffset, BackgroundSprite, BackgroundSourcePosition, BackgroundSize);
}

//-------------------------------------------------------------------------------------------
void FMaze::DrawPellets() const
{
	for(int y = 0; y < Rows; y++)
	{
		for(int x = 0; x < Columns; x++)
		{
			const int GridIndex = y * Columns + x;
			const FTile QueryTile =  Grid.at(GridIndex);
			if(QueryTile.bHasPellet || QueryTile.bHasEnergizer)
			{
				olc::vf2d PelletPosition = { static_cast<float>(x), static_cast<float>(y) };
				PelletPosition *= TileSize;
				PelletPosition += TileCenter;
				PelletPosition.y -= 1;

				olc::vf2d Size = {1.0f, 1.0f};

				if(QueryTile.bHasPellet)
				{
					Engine->FillRect(PelletPosition, Size, PelletColor);
				}
				else
				{
					Engine->FillCircle(PelletPosition, 4, PelletColor);
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
void FMaze::DrawFruit() const
{
	float OffsetX = BonusFruitCount * 16.0f;
	const olc::vf2d ImageOffset = {OffsetX, 0.0f};
	Engine->DrawPartialDecal(FruitLocation, FruitDecal, ImageOffset, FruitSize);
}

//-------------------------------------------------------------------------------------------
void FMaze::DrawScore() const
{
	float OffsetX = (BonusFruitCount - 1) * 16.0f;
	const olc::vf2d ImageOffset = {OffsetX, 0.0f};
	Engine->DrawPartialDecal(FruitLocation, FruitPointsDecal, ImageOffset, FruitSize);
}

//-------------------------------------------------------------------------------------------
void FMaze::CreateGrid()
{
	for (int y = 0; y < Rows; y++)
	{
		for (int x = 0; x < Columns; x++)
		{
			olc::vf2d QueryPosition = { static_cast<float>(x), static_cast<float>(y) };

			FTile NewTile;
			QueryPosition *= TileSize;
			
			olc::Pixel Query = TileMap->GetPixel(QueryPosition);

			if (Query == olc::RED)
			{
				NewTile.bIsObstacle = true;
			}
			else if (Query == olc::WHITE)
			{
				NewTile.bHasPellet = true;
			}
			else if (Query == olc::CYAN)
			{
				NewTile.bHasPellet = true;
				NewTile.bIsIntersection = true;
			}
			else if (Query == olc::YELLOW)
			{
				NewTile.bIsIntersection = true;
			}
			else if (Query == olc::BLUE)
			{
				NewTile.bHasEnergizer = true;
			}
			else if (Query == olc::MAGENTA)
			{
				NewTile.bHasEnergizer = true;
				NewTile.bIsIntersection = true;
			}
			
			NewTile.TileID = y * Columns + x;

			Grid.push_back(NewTile);

		}
	}
}

//-------------------------------------------------------------------------------------------
void FMaze::EatPellet(const olc::vf2d& Position)
{
	--Pellets;
	
	if(GetTile(Position).bHasPellet)
	{
		GetTile(Position).bHasPellet = false;
	}
	else
	{
		GetTile(Position).bHasEnergizer = false;
	}

	olc::vf2d PositionFromCenter;
	GetPositionToTileCenter(Position, PositionFromCenter);
	const olc::vf2d DrawPoint = Position + PositionFromCenter - TileCenter;
	Engine->FillRect(DrawPoint, TileSize, olc::BLACK);
}

//-------------------------------------------------------------------------------------------
int FMaze::EatFruit()
{
	bHasFruit = false;
	bDisplayFruitScore = true;
	if(BonusFruitCount == 0)
	{
		++BonusFruitCount;
		return 100;
	}
	++BonusFruitCount;
	return 300;
}

//-------------------------------------------------------------------------------------------
bool FMaze::HasFruit() const
{
	return bHasFruit;
}

//-------------------------------------------------------------------------------------------
const FMaze::FTile& FMaze::GetTile(const olc::vf2d& Position) const
{
	const olc::vf2d NewPos = Position / 8.0f;
	const int GridIndex = floor(NewPos.y) * Columns + floor(NewPos.x);
	return Grid.at(GridIndex);
}

//-------------------------------------------------------------------------------------------
FMaze::FTile& FMaze::GetTile(const olc::vf2d& Position)
{
	const olc::vf2d NewPos = Position / 8.0f;
	const int GridIndex = floor(NewPos.x) + Columns * floor(NewPos.y);
	return Grid.at(GridIndex);
}

//-------------------------------------------------------------------------------------------
void FMaze::GetPositionToTileCenter(const olc::vf2d& Position, olc::vf2d& OutPosition) const
{
	const olc::vi2d NewPos = {static_cast<int>(floor(Position.x)) % 8, static_cast<int>(floor(Position.y)) % 8};
	OutPosition = TileCenter - NewPos;
}

//-------------------------------------------------------------------------------------------
void FMaze::GetDirectionFromTileCenter(const olc::vf2d& Position, olc::vf2d& OutDirection) const
{
	GetPositionToTileCenter(Position, OutDirection);
	OutDirection *= -1;
	OutDirection = OutDirection.norm();
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsCenter(const olc::vf2d& Position) const
{
	const olc::vi2d NewPos = {static_cast<int>(floor(Position.x)) % 8, static_cast<int>(floor(Position.y)) % 8};
	return NewPos == TileCenter;
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsNextTileObstacle(const olc::vf2d& Position, const olc::vf2d& Direction)
{
	return GetTile(FBasePawn::WrapCoordinates(Engine, Position + Direction * TileSize)).bIsObstacle;
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsTunnel(const olc::vf2d& Position) const
{
	FTile CurrentTile = GetTile(Position);
	for(int i : Tunnel)
	{
		if(CurrentTile.TileID == i)
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsForbiddenZone(const olc::vf2d& Position) const
{
	FTile CurrentTile = GetTile(Position);
	for(int i : ForbiddenZone)
	{
		if(CurrentTile.TileID == i)
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsFruitSpawn(const olc::vf2d& Position) const
{
	return GetTile(Position).TileID == FruitLocationTileID;
}

//-------------------------------------------------------------------------------------------
void FMaze::GetNeighbors(const olc::vf2d& Position, FMaze::FTile& Up, FMaze::FTile& Down, FMaze::FTile& Left, FMaze::FTile& Right)
{
	FBasePawn::WrapCoordinates(Engine, Position);
	
	Up = GetTile({Position.x, Position.y - 8.0f});
	Down = GetTile({Position.x, Position.y + 8.0f});
	Left = GetTile({Position.x - 8.0f, Position.y});
	Right = GetTile({Position.x + 8.0f, Position.y});
}

//-------------------------------------------------------------------------------------------
void FMaze::GetCenterOfTile(const olc::vf2d& Position, olc::vf2d& Center) const
{
	GetPositionToTileCenter(Position, Center);
	Center = Position - Center;
}

