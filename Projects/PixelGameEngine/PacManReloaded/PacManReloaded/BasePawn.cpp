#include "BasePawn.h"

//-------------------------------------------------------------------------------------------
FBasePawn::FBasePawn(olc::PixelGameEngine* InEngine, olc::Sprite* InSprite, FMaze* InMaze)
{
	BaseSprite = InSprite;
	BaseDecal = new olc::Decal(BaseSprite);

	Maze = InMaze;
	Engine = InEngine;
}

//-------------------------------------------------------------------------------------------
FBasePawn::~FBasePawn()
{
	delete BaseDecal;
}

//-------------------------------------------------------------------------------------------
void FBasePawn::Update(const float ElapsedTime, const float RoundTime)
{
	Move(ElapsedTime);
	DrawSelf(RoundTime);
}

//-------------------------------------------------------------------------------------------
void FBasePawn::SetDirection(const olc::vf2d& NewDirection)
{
	//Can't run into an obstacle
	if(Maze->IsNextTileObstacle(Position, NewDirection))
	{
		return;
	}
	//Change according to input
	Direction = NewDirection;
	
}

//-------------------------------------------------------------------------------------------
void FBasePawn::Move(const float ElapsedTime)
{
	//Can't move if paused or if an obstacle is in the way
	if(bIsPaused || (Maze->IsCenter(Position) && Maze->IsNextTileObstacle(Position, Direction)))
	{
		return;
	}
	//Takes into account the additional Tunnel Multiplier for speed. This is adjusted in each instance's update.
	Position = WrapCoordinates(Engine, Position + BaseSpeed * std::min(SpeedMultiplier, TunnelMultiplier) * ElapsedTime * Direction);
}

//-------------------------------------------------------------------------------------------
void FBasePawn::DrawSelf(const float RoundTime) const
{
	if (BaseDecal)
	{
		//Sprite Direction Offset 
		float OffsetX = 0.0f;

		//We don't compare these stricly to UP, DOWN, LEFT or RIGHT since a turn temporarily changes their direction
		//to be a combination of the two.s
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
		//Based on RoundTime, switch between the two frame animation every couple of frames
		if(static_cast<int>(floor(12 * RoundTime)) % 2 == 0)
		{
			OffsetX += 16.0f;
		}

		const olc::vf2d ImageOffset = {OffsetX, 0.0f};
		Engine->DrawPartialDecal(Position - CenterOffset, BaseDecal, ImageOffset, Size);
	}
	else
	{
		//Without Sprites or Decals
		Engine->Draw(Position, olc::YELLOW);
	}
}

//-------------------------------------------------------------------------------------------
olc::vf2d& FBasePawn::GetPosition()
{
	return Position;
}

//-------------------------------------------------------------------------------------------
olc::vf2d& FBasePawn::GetDirection()
{
	return Direction;
}

//-------------------------------------------------------------------------------------------
void FBasePawn::Pause()
{
	bIsPaused = true;
}

//-------------------------------------------------------------------------------------------
void FBasePawn::UnPause()
{
	bIsPaused = false;
}

//-------------------------------------------------------------------------------------------
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
