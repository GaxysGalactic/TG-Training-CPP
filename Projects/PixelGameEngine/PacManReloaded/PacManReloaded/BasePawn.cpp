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

void FBasePawn::SetDirection(const olc::vf2d& NewDirection)
{
	Direction = NewDirection;
}

void FBasePawn::Move(olc::PixelGameEngine* Engine, const float ElapsedTime)
{
	
	Position = WrapCoordinates(Engine, Position + BaseSpeed * SpeedMultiplier * ElapsedTime * Direction);
}

void FBasePawn::DrawSelf(olc::PixelGameEngine* Engine, const float RoundTime) const
{
	//TODO: Animation would depend on Timer made from ElapsedTime, flip every second

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

		if(int(floor(8*RoundTime)) % 2 == 0)
		{
			OffsetX += 16.0f;
		}

		olc::vf2d ImageOffset = {OffsetX, 0.0f};
		//This below could be made into member variable. Also, idea about .center() function.
		olc::vf2d CenterOffset = {6.0f, 7.0f};
		Engine->DrawPartialDecal(Position - CenterOffset, BaseDecal, ImageOffset, Size);
	}
	else
	{
		//Without Sprites or Decals
		Engine->Draw(Position, olc::YELLOW);
		//Engine->DrawLine(Position, Position + Direction * 10, olc::RED);
	}
}

olc::vf2d FBasePawn::WrapCoordinates(olc::PixelGameEngine* Engine, const olc::vf2d& InVector)
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
