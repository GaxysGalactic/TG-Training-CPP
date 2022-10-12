#include "Maze.h"

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
	Engine->DrawPartialSprite(BackgroundOffset, BackgroundSprite, BackgroundSourcePosition, BackgroundSize);

	Engine->DrawLine(51, 212, 171, 212);
}

void FMaze::CreateGrid()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			olc::vf2d QueryPosition = { float(j), float(i) };

			FTile NewTile;
			QueryPosition *= TileSize;
			
			olc::Pixel Query = TileMap->GetPixel(QueryPosition);

			if (TileMap->GetPixel(QueryPosition) == olc::RED)
			{
				NewTile.bIsObstacle = true;
			}
			else if (TileMap->GetPixel(QueryPosition) == olc::WHITE)
			{
				NewTile.bHasPellet = true;
			}
			else if (TileMap->GetPixel(QueryPosition) == olc::CYAN)
			{
				NewTile.bHasPellet = true;
				NewTile.bIsIntersection = true;
			}
			else if (TileMap->GetPixel(QueryPosition) == olc::YELLOW)
			{
				NewTile.bIsIntersection = true;
			}
			else if (TileMap->GetPixel(QueryPosition) == olc::BLUE)
			{
				NewTile.bHasEnergizer = true;
			}
			else if (TileMap->GetPixel(QueryPosition) == olc::MAGENTA)
			{
				NewTile.bHasEnergizer = true;
				NewTile.bIsIntersection = true;
			}

			Grid.push_back(NewTile);

		}
	}

}

const FMaze::FTile& FMaze::GetTile(const olc::vf2d Position) const
{
	olc::vf2d NewPos = Position / TileSize;
	int GridIndex = NewPos.x * Columns + NewPos.y;
	return Grid.at(GridIndex);
}

FMaze::FTile& FMaze::GetTile(const olc::vf2d Position)
{
	olc::vf2d NewPos = Position / TileSize;
	int GridIndex = NewPos.x * Columns + NewPos.y;
	return Grid.at(GridIndex);
}

void FMaze::GetNeighbors(const olc::vf2d Position, FTile* Up, FTile* Down, FTile* Left, FTile* Right)
{
	Up = &GetTile({Position.x, Position.y - 8.0f});
	Down = &GetTile({Position.x, Position.y + 8.0f});

	//TODO: Change this to be compatible with tunnel
	Left = &GetTile({Position.x - 8.0f, Position.y});
	Right = &GetTile({Position.x + 8.0f, Position.y});
}

