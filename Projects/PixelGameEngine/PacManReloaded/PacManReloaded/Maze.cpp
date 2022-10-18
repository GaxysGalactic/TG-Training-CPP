#include "Maze.h"

#include "BasePawn.h"

FMaze::FMaze(olc::Sprite* InBackground, olc::Sprite* InTileMap)
{
	BackgroundSprite = InBackground;
	TileMap = InTileMap;
	CreateGrid();
}

FMaze::~FMaze()
{
	delete BackgroundSprite;
}

void FMaze::DrawBase(olc::PixelGameEngine* Engine) const
{
	//Engine->DrawPartialSprite(BackgroundOffset, BackgroundSprite, BackgroundSourcePosition, BackgroundSize);
	olc::vf2d SourcePos = {0.0f, 0.0f};
	Engine->DrawPartialSprite(BackgroundOffset, BackgroundSprite, SourcePos, BackgroundSize);
	//Engine->DrawSprite(0,0, TileMap);
	//Engine->DrawLine(51, 212, 171, 212);
}

void FMaze::DrawPellets(olc::PixelGameEngine* Engine) const
{
	for(int i = 0; i < Rows; i++)
	{
		for(int j = 0; j < Columns; j++)
		{
			const int GridIndex = i * Columns + j;
			FTile QueryTile =  Grid.at(GridIndex);
			if(QueryTile.bHasPellet || QueryTile.bHasEnergizer)
			{
				olc::vf2d PelletPosition = { static_cast<float>(j), static_cast<float>(i) };
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

void FMaze::CreateGrid()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			olc::vf2d QueryPosition = { static_cast<float>(j), static_cast<float>(i) };

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
			
			NewTile.TileID = i * Columns + j;

			Grid.push_back(NewTile);

		}
	}

}

void FMaze::EatPellet(olc::PixelGameEngine* Engine, const olc::vf2d& Position)
{
	--Pellets;
	
	//Add energizer here too maybe
	if(GetTile(Position).bHasPellet)
	{
		GetTile(Position).bHasPellet = false;
	}
	else
	{
		GetTile(Position).bHasEnergizer = false;
	}

	//Adjust this so its start of tile - its a bit buggy
	olc::vf2d PositionFromCenter;
	GetPositionFromTileCenter(Position, PositionFromCenter);
	olc::vf2d DrawPoint = Position + PositionFromCenter - TileCenter;
	olc::vf2d Size = {8.0f, 8.0f};
	Engine->FillRect(DrawPoint, Size, olc::BLACK);
}

const FMaze::FTile& FMaze::GetTile(const olc::vf2d& Position) const
{
	const olc::vf2d NewPos = Position / 8.0f;
	const int GridIndex = floor(NewPos.x) + Columns * floor(NewPos.y);
	return Grid.at(GridIndex);
}

FMaze::FTile& FMaze::GetTile(const olc::vf2d& Position)
{
	const olc::vf2d NewPos = Position / 8.0f;
	const int GridIndex = floor(NewPos.x) + Columns * floor(NewPos.y);
	return Grid.at(GridIndex);
}

void FMaze::GetPositionFromTileCenter(const olc::vf2d& Position, olc::vf2d& OutPosition) const
{
	olc::vi2d NewPos = {static_cast<int>(floor(Position.x)) % 8, static_cast<int>(floor(Position.y)) % 8};
	OutPosition = TileCenter - NewPos;
}

void FMaze::GetDirectionToTileCenter(const olc::vf2d& Position, olc::vf2d& OutDirection) const
{
	GetPositionFromTileCenter(Position, OutDirection);
	OutDirection *= -1;
	OutDirection = OutDirection.norm();
}

bool FMaze::IsPixelACenter(const olc::vf2d& Position) const
{
	olc::vi2d NewPos = {static_cast<int>(floor(Position.x)) % 8, static_cast<int>(floor(Position.y)) % 8};
	return NewPos == TileCenter;
}

bool FMaze::IsNextTileAnObstacle(const olc::PixelGameEngine* Engine, const olc::vf2d& Position, const olc::vf2d& Direction)
{
	//TODO: Fix borders
	return GetTile(FBasePawn::WrapCoordinates(Engine, Position + Direction * TileSize)).bIsObstacle;
}

void FMaze::GetNeighbors(olc::PixelGameEngine* Engine, const olc::vf2d& Position, FMaze::FTile& Up, FMaze::FTile& Down, FMaze::FTile& Left, FMaze::FTile& Right)
{
	FBasePawn::WrapCoordinates(Engine, Position);
	
	Up = GetTile({Position.x, Position.y - 8.0f});
	Down = GetTile({Position.x, Position.y + 8.0f});
	Left = GetTile({Position.x - 8.0f, Position.y});
	Right = GetTile({Position.x + 8.0f, Position.y});
}

void FMaze::GetCenterOfTile(const olc::vf2d& Position, olc::vf2d& Center) const
{
	GetPositionFromTileCenter(Position, Center);
	Center = Position - Center;
}

