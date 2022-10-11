#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"

// Override base class with your custom functionality
class FPacMan : public olc::PixelGameEngine
{
	olc::Sprite* SpriteDemo = nullptr;
	olc::Decal* DecalDemo = nullptr;

	FPlayer* Pacman;
	olc::Sprite* PacmanSprite = nullptr;

	float RoundTime = 0.0f;


	//For the grid, it should read an image nTilesW x nTilesH in terms of pixels for optimization and easier reading
	//Each grid slot should be a FTile class? It should maybe know its inmediate neighbours
	//... like Up, Down, Left, Right...
	//Should have booleans for Obstacle, Pellet, Energizer, Fruit.

public:

	FPacMan()
	{
		sAppName = "Pac-Man: Reloaded";
	}
	
	bool OnUserCreate() override
	{
		
		SpriteDemo = new olc::Sprite("./Sprites/Spritesheet.png");
		DecalDemo = new olc::Decal(SpriteDemo);

		PacmanSprite = new olc::Sprite("./Sprites/PacMan.png");
		Pacman = new FPlayer(PacmanSprite);

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		RoundTime += ElapsedTime;
		
		Clear(olc::BLACK);

		olc::vf2d BGOffset = { 0.0f, 24.0f };
		olc::vf2d BGSourcePos = { 228.0f, 0.0f };
		olc::vf2d BGSize = { 224.0f, 248.0f };

		//DrawPartialDecal(BGOffset, DecalDemo, BGSourcePos, BGSize);
		DrawPartialSprite(BGOffset, SpriteDemo, BGSourcePos, BGSize);
		Pacman->Update(this, ElapsedTime, RoundTime);

		return true;
	}

	bool Draw(const olc::vi2d& pos, olc::Pixel p = olc::WHITE)
	{
		olc::vi2d NewPos = FBasePawn::WrapCoordinates(this, pos);
		return olc::PixelGameEngine::Draw(pos, p);
	}
	
	
};

int main()
{
	FPacMan Game;
	if (Game.Construct(224, 288, 3, 3))
		Game.Start();
	return 0;
}
