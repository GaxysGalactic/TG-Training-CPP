#include "BasePawn.h"

FBasePawn::FBasePawn()
{

}

FBasePawn::FBasePawn(olc::Sprite* InSprite)
{
	BaseSprite = InSprite;
	BaseDecal = new olc::Decal(BaseSprite);
}

FBasePawn::~FBasePawn()
{
	delete BaseSprite;
}

void FBasePawn::Update(olc::PixelGameEngine* Engine, const float ElapsedTime)
{
	Move(ElapsedTime);
	DrawSelf(Engine);
}

void FBasePawn::SetDirection(const olc::vf2d& NewDirection)
{
	Direction = NewDirection;
}

void FBasePawn::Move(const float ElapsedTime)
{
	Position += Speed * ElapsedTime * Direction;
}

void FBasePawn::DrawSelf(olc::PixelGameEngine* Engine)
{
	//TODO: Animation would depend on Timer made from ElapsedTime, flip every second

	if (BaseDecal)
	{
		//TODO: Draw Based on direction and spritesheet. PacMan's should be adjusted to match the Ghosts for easier use.
		
	}
}
