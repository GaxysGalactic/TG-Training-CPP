#include "Maze.h"

#include "BasePawn.h"

//-------------------------------------------------------------------------------------------
FMaze::FMaze(olc::PixelGameEngine* InEngine, olc::Sprite* InBackground, olc::Sprite* InTileMap)
{
	Engine = InEngine;
	BackgroundSprite = InBackground;
	TileMap = InTileMap;
	CreateGrid();
}

//-------------------------------------------------------------------------------------------
FMaze::~FMaze()
{
	delete BackgroundSprite;
	delete TileMap;
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
bool FMaze::IsPixelACenter(const olc::vf2d& Position) const
{
	const olc::vi2d NewPos = {static_cast<int>(floor(Position.x)) % 8, static_cast<int>(floor(Position.y)) % 8};
	return NewPos == TileCenter;
}

//-------------------------------------------------------------------------------------------
bool FMaze::IsNextTileAnObstacle(const olc::vf2d& Position, const olc::vf2d& Direction)
{
	return GetTile(FBasePawn::WrapCoordinates(Engine, Position + Direction * TileSize)).bIsObstacle;
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

