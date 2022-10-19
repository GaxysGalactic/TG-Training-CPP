#include "BasePawn.h"

FBasePawn::FBasePawn(olc::Sprite* InSprite, FMaze* InMaze)
{
	BaseSprite = InSprite;
	BaseDecal = new olc::Decal(BaseSprite);

	Maze = InMaze;
}

FBasePawn::~FBasePawn()
{
	delete BaseSprite;
}

void FBasePawn::Update(olc::PixelGameEngine* Engine, const float ElapsedTime, const float RoundTime)
{
	Move(Engine, ElapsedTime);
	DrawSelf(Engine, RoundTime);
}

void FBasePawn::SetDirection(const olc::PixelGameEngine* Engine, const olc::vf2d& NewDirection)
{
	//Can't run into an obstacle
	if(Maze->IsNextTileAnObstacle(Engine, Position, NewDirection))
	{
		return;
	}
	//Change according to input
	Direction = NewDirection;
	
}

void FBasePawn::Move(const olc::PixelGameEngine* Engine, const float ElapsedTime)
{
	if(Maze->IsPixelACenter(Position) && Maze->IsNextTileAnObstacle(Engine, Position, Direction))
	{
		return;
	}
	Position = WrapCoordinates(Engine, Position + BaseSpeed * SpeedMultiplier * ElapsedTime * Direction);
}

void FBasePawn::DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const
{
	if (BaseDecal)
	{
		float OffsetX = 0.0f;

		if(Direction.x == 1.0f)
		{
			OffsetX = 0.0f;
		}
		else if(Direction.x == -1.0f)
		{
			OffsetX = 32.0f;
		}
		else if(Direction.y == -1.0f)
		{
			OffsetX = 64.0f;
		}
		else if(Direction.y == 1.0f)
		{
			OffsetX = 96.0f;
		}

		//Animation
		if(static_cast<int>(floor(12 * RoundTime)) % 2 == 0)
		{
			OffsetX += 16.0f;
		}

		const olc::vf2d ImageOffset = {OffsetX, 0.0f};
		const olc::vf2d CenterOffset = {7.0f, 8.0f};
		Engine->DrawPartialDecal(Position - CenterOffset, BaseDecal, ImageOffset, Size);
	}
	else
	{
		//Without Sprites or Decals
		Engine->Draw(Position, olc::YELLOW);
		//Engine->DrawLine(Position, Position + Direction * 10, olc::RED);
	}
}

olc::vf2d& FBasePawn::GetPosition()
{
	return Position;
}

olc::vf2d& FBasePawn::GetDirection()
{
	return Direction;
}

olc::vf2d FBasePawn::WrapCoordinates(const olc::PixelGameEngine* Engine, const olc::vf2d& InVector)
{
	olc::vf2d OutVector = InVector;
	
	if (InVector.x < 0.0f)
	{
		OutVector.x = InVector.x + static_cast<float>(Engine->ScreenWidth());
	}
	if (InVector.x >= static_cast<float>(Engine->ScreenWidth()))
	{
		OutVector.x = InVector.x - static_cast<float>(Engine->ScreenWidth());
	}

	if (InVector.y < 0.0f)
	{
		OutVector.y = InVector.y + static_cast<float>(Engine->ScreenHeight());
	}
	if (InVector.y >= static_cast<float>(Engine->ScreenHeight()))
	{
		OutVector.y = InVector.y - static_cast<float>(Engine->ScreenHeight());
	}

	return OutVector;
}
