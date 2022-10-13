#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Maze.h"

// Override base class with your custom functionality
class FPacMan : public olc::PixelGameEngine
{
	//Sprites and Decals
	olc::Sprite* BackgroundSprite = nullptr;
	olc::Decal* BackgroundDecal = nullptr;
	olc::Sprite* PacmanSprite = nullptr;
	olc::Sprite* TileMapSprite = nullptr;

	//Instances
	FMaze* Maze;
	FPlayer* Pacman;

	//Ghosts should be FGhost? or FNAME?

	//Stats
	float RoundTime = 0.0f;

public:

	FPacMan()
	{
		sAppName = "Pac-Man: Reloaded";
	}
	
	bool OnUserCreate() override
	{
		//LOAD SPRITES & DECALS
		LoadSprites();

		//BACKGROUND & GRID
		Clear(olc::BLACK);
		Maze = new FMaze(BackgroundSprite, TileMapSprite);
		Maze->DrawBase(this);

		//DRAW PELLETS
		//Maze->DrawPellets(this);

		//CHARACTERS
		Pacman = new FPlayer(PacmanSprite, Maze);
		//Pacman = new FPlayer();
		
		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		RoundTime += ElapsedTime;

		if(ElapsedTime > 2.0f)
		{
			ElapsedTime = 0.01f;
		}
		
		Pacman->Update(this, ElapsedTime, RoundTime);

		return true;
	}

	bool Draw(const olc::vi2d& pos, olc::Pixel p = olc::WHITE)
	{
		olc::vi2d NewPos = FBasePawn::WrapCoordinates(this, pos);
		return olc::PixelGameEngine::Draw(pos, p);
	}

private:

	void LoadSprites()
	{
		BackgroundSprite = new olc::Sprite("./Sprites/Spritesheet.png");
		BackgroundDecal = new olc::Decal(BackgroundSprite);
		PacmanSprite = new olc::Sprite("./Sprites/PacMan.png");
		TileMapSprite = new olc::Sprite("./Sprites/TileMap.png");
	}
	
};

int main()
{
	FPacMan Game;
	if (Game.Construct(224, 288, 3, 3))
		Game.Start();
	return 0;
}
