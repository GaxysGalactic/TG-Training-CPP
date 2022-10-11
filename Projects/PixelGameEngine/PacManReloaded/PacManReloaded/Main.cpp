#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class FPacMan : public olc::PixelGameEngine
{
public:
	FPacMan()
	{
		sAppName = "Pac-Man: Reloaded";
	}

	olc::Sprite* SpriteDemo = nullptr;
	olc::Decal* DecalDemo = nullptr;

public:
	bool OnUserCreate() override
	{
		SpriteDemo = new olc::Sprite("./Sprites/Spritesheet.png");
		DecalDemo = new olc::Decal(SpriteDemo);

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		Clear(olc::BLACK);

		olc::vf2d BGOffset = { 0.0f, 24.0f };
		olc::vf2d BGSourcePos = { 228.0f, 0.0f };
		olc::vf2d BGSize = { 224.0f, 248.0f };

		DrawPartialDecal(BGOffset, DecalDemo, BGSourcePos, BGSize);

		return true;
	}
};

int main()
{
	FPacMan Game;
	if (Game.Construct(224, 288, 3, 3))
		Game.Start();
	return 0;
}
