#define OLC_PGE_APPLICATION
#include "Blinky.h"
#include "Clyde.h"
#include "Ghost.h"
#include "Inky.h"
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Maze.h"
#include "Pinky.h"

// Override base class with your custom functionality
class FPacMan : public olc::PixelGameEngine
{
	//Sprites and Decals
	olc::Sprite* BackgroundSprite = nullptr;
	olc::Decal* BackgroundDecal = nullptr;
	olc::Sprite* PacmanSprite = nullptr;
	olc::Sprite* PacmanDeathSprite = nullptr;
	olc::Sprite* TileMapSprite = nullptr;

	olc::Sprite* FrightenedSprite = nullptr;
	olc::Sprite* EatenSprite = nullptr;
	
	olc::Sprite* BlinkySprite = nullptr;
	olc::Sprite* InkySprite = nullptr;
	olc::Sprite* PinkySprite = nullptr;
	olc::Sprite* ClydeSprite = nullptr;

	//Instances
	FMaze* Maze;
	FPlayer* Pacman;
	FBlinky* Blinky;
	FInky* Inky;
	FPinky* Pinky;
	FClyde* Clyde;

	//Ghost array
	std::vector<FGhost*> Ghosts;

	//Stats
	float RoundTime = 0.0f;
	bool bEnded = false;
	float GameOverTimer = 0.0f;

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
		DrawString(24, 1, "1UP");
		DrawString(72, 1, "HIGH SCORE");

		//DRAW PELLETS & ENERGIZERS
		//Maze->DrawPellets(this);

		//CHARACTERS
		Pacman = new FPlayer(PacmanSprite, Maze, PacmanDeathSprite);
		//Pacman = new FPlayer();
		//GhostTest = new FGhost(BlinkySprite, Maze, FrightenedSprite, EatenSprite, Pacman);
		Blinky = new FBlinky(BlinkySprite, Maze, FrightenedSprite, EatenSprite, Pacman);
		Inky = new FInky(InkySprite, Maze, FrightenedSprite, EatenSprite, Pacman, Blinky);
		Pinky = new FPinky(PinkySprite, Maze, FrightenedSprite, EatenSprite, Pacman);
		Clyde = new FClyde(ClydeSprite, Maze, FrightenedSprite, EatenSprite, Pacman);

		Ghosts.push_back(Blinky);
		Ghosts.push_back(Inky);
		Ghosts.push_back(Pinky);
		Ghosts.push_back(Clyde);
		
		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		if(!bEnded)
		{
			RoundTime += ElapsedTime;

			//Debugging
			if(ElapsedTime > 2.0f)
			{
				ElapsedTime = 0.01f;
			}
		
			Pacman->Update(this, ElapsedTime, RoundTime);
			Blinky->Update(this, ElapsedTime, RoundTime);
			Inky->Update(this, ElapsedTime, RoundTime);
			Pinky->Update(this, ElapsedTime, RoundTime);
			Clyde->Update(this, ElapsedTime, RoundTime);

			if(Pacman->IsEnergized())
			{
				FrightenGhosts();
				Pacman->SetEnergized(false);
			}
			
			CheckCollision();

			DrawScore();

			if(!bEnded)
			{
				bEnded = HasWon();
			}
		}
		else
		{
			if(HasWon())
			{
				Clear(olc::BLACK);
				DrawString(80, 110, "YOU WON!");
				DrawString(30, 118, "Press SPACE to exit.");	
			}
			else
			{
				GameOverTimer += ElapsedTime;
				Pacman->Update(this, ElapsedTime, RoundTime);
				if(GameOverTimer >= 3.0f)
				{
					Clear(olc::BLACK);
					DrawString(80, 110, "GAME OVER");
					DrawString(30, 118, "Press SPACE to exit.");	
				}
			}

			if(GetKey(olc::Key::SPACE).bPressed)
			{
				return false;
			}
			
		}
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
		PacmanDeathSprite = new olc::Sprite("./Sprites/PacManDeath.png");

		FrightenedSprite = new olc::Sprite("./Sprites/Frightened.png");
		EatenSprite = new olc::Sprite("./Sprites/Dead.png");
		
		BlinkySprite = new olc::Sprite("./Sprites/Blinky.png");
		PinkySprite = new olc::Sprite("./Sprites/Pinky.png");
		InkySprite = new olc::Sprite("./Sprites/Inky.png");
		ClydeSprite = new olc::Sprite("./Sprites/Clyde.png");
		
		TileMapSprite = new olc::Sprite("./Sprites/TileMap.png");
	}

	void CheckCollision()
	{
		for(FGhost* Ghost: Ghosts)
		{
			if(Maze->GetTile(Pacman->GetPosition()).TileID == Maze->GetTile(Ghost->GetPosition()).TileID)
			{
				if(Ghost->CanBeEaten())
				{
					Ghost->Die();
				}
				else if (!Ghost->IsDead())
				{
					Pacman->Die();
					bEnded = true;
				}
			}
		}
	}

	void FrightenGhosts()
	{
		for(FGhost* Ghost: Ghosts)
		{
			Ghost->Frighten();
		}
	}

	void DrawScore()
	{
		olc::vi2d DrawPoint = {24, 9};
		DrawStringDecal(DrawPoint, std::to_string(Pacman->GetScore()));
	}

	bool HasWon()
	{
		return Maze->Pellets == 0;
	}
	
};

int main()
{
	FPacMan Game;
	if (Game.Construct(224, 288, 3, 3))
		Game.Start();
	return 0;
}
