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
	olc::Sprite* TileMapSprite = nullptr;

	olc::Sprite* FruitSprite = nullptr;
	olc::Sprite* FruitPointsSprite = nullptr;
	
	olc::Sprite* PacmanSprite = nullptr;
	olc::Sprite* PacmanDeathSprite = nullptr;
	olc::Sprite* GhostPointsSprite = nullptr;

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
	bool bIsPaused = false;
	float PauseTimer = 0.0f;
	const olc::vi2d ScoreDrawPoint = {24, 9};

public:

	//-------------------------------------------------------------------------------------------
	FPacMan()
	{
		sAppName = "Pac-Man: Reloaded";
	}

	//-------------------------------------------------------------------------------------------
	bool OnUserCreate() override
	{
		//LOAD SPRITES & DECALS
		LoadSprites();

		//BACKGROUND & GRID
		LoadBackground();

		//CHARACTERS
		InitializeCharacters();
		
		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool OnUserUpdate(float ElapsedTime) override
	{
		//Switches to end screen if lost or won
		if(!bEnded)
		{
			LoopGameplay(ElapsedTime);

			if(!bEnded)
			{
				bEnded = HasWon();
			}
		}
		else
		{
			EndGame(HasWon(), ElapsedTime);

			if(GetKey(olc::Key::SPACE).bPressed)
			{
				return false;
			}
			
		}
		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool OnUserDestroy() override
	{
		//Deletes all the dynamically allocated memory...
		delete BackgroundSprite;
		delete BackgroundDecal;
		delete PacmanSprite;
		delete PacmanDeathSprite;
		delete TileMapSprite;

		delete FrightenedSprite;
		delete EatenSprite;
	
		delete BlinkySprite;
		delete InkySprite;
		delete PinkySprite;
		delete ClydeSprite;
		
		delete Maze;
		delete Pacman;
		delete Blinky;
		delete Inky;
		delete Pinky;
		delete Clyde;
		
		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool Draw(const olc::vi2d& pos, olc::Pixel p = olc::WHITE)
	{
		olc::vi2d NewPos = FBasePawn::WrapCoordinates(this, pos);
		return olc::PixelGameEngine::Draw(pos, p);
	}

private:

	//-------------------------------------------------------------------------------------------
	void LoadSprites()
	{
		BackgroundSprite = new olc::Sprite("./Sprites/Spritesheet.png");
		BackgroundDecal = new olc::Decal(BackgroundSprite);

		FruitSprite = new olc::Sprite("./Sprites/BonusFruit.png");
		FruitPointsSprite = new olc::Sprite("./Sprites/BonusFruitPoints.png"),
		
		PacmanSprite = new olc::Sprite("./Sprites/PacMan.png");
		PacmanDeathSprite = new olc::Sprite("./Sprites/PacManDeath.png");
		GhostPointsSprite = new olc::Sprite("./Sprites/GhostPoints.png");

		FrightenedSprite = new olc::Sprite("./Sprites/Frightened.png");
		EatenSprite = new olc::Sprite("./Sprites/Dead.png");
		
		BlinkySprite = new olc::Sprite("./Sprites/Blinky.png");
		PinkySprite = new olc::Sprite("./Sprites/Pinky.png");
		InkySprite = new olc::Sprite("./Sprites/Inky.png");
		ClydeSprite = new olc::Sprite("./Sprites/Clyde.png");
		
		TileMapSprite = new olc::Sprite("./Sprites/TileMap.png");
	}

	//-------------------------------------------------------------------------------------------
	void LoadBackground()
	{
		Clear(olc::BLACK);
		Maze = new FMaze(this, BackgroundSprite, TileMapSprite, FruitSprite, FruitPointsSprite);
		Maze->DrawBase();
		DrawString(24, 1, "1UP");
		DrawString(72, 1, "HIGH SCORE");
	}

	//-------------------------------------------------------------------------------------------
	void InitializeCharacters()
	{
		Pacman = new FPlayer(this, PacmanSprite, Maze, PacmanDeathSprite, GhostPointsSprite);
		Blinky = new FBlinky(this, BlinkySprite, Maze, FrightenedSprite, EatenSprite, Pacman);
		Inky = new FInky(this, InkySprite, Maze, FrightenedSprite, EatenSprite, Pacman, Blinky);
		Pinky = new FPinky(this, PinkySprite, Maze, FrightenedSprite, EatenSprite, Pacman);
		Clyde = new FClyde(this, ClydeSprite, Maze, FrightenedSprite, EatenSprite, Pacman);

		//Places all the ghosts in an array for easier iteration later...
		Ghosts.push_back(Blinky);
		Ghosts.push_back(Inky);
		Ghosts.push_back(Pinky);
		Ghosts.push_back(Clyde);
	}

	//-------------------------------------------------------------------------------------------
	void LoopGameplay(float ElapsedTime)
	{
		//Debugging
		if(ElapsedTime > 1.0f)
		{
			ElapsedTime = 0.01f;
		}
		
		//Update Timers
		RoundTime += ElapsedTime;

		if(bIsPaused)
		{
			PauseTimer += ElapsedTime;

			if(PauseTimer >= 1.0f)
			{
				UnPauseCharacters();
			}
		}

		//Update Characters
		UpdateCharacters(ElapsedTime);

		//Frighten Ghosts if needed
		if(Pacman->IsEnergized())
		{
			FrightenGhosts();
			Pacman->SetIsEnergized(false);
		}

		//Check collision between player and ghosts
		CheckCollision();

		DrawScore();
	}

	//-------------------------------------------------------------------------------------------
	void UpdateCharacters(const float ElapsedTime) const
	{
		Pacman->Update(ElapsedTime, RoundTime);
		Blinky->Update(ElapsedTime, RoundTime);
		Inky->Update(ElapsedTime, RoundTime);
		Pinky->Update(ElapsedTime, RoundTime);
		Clyde->Update(ElapsedTime, RoundTime);

		Maze->Update(ElapsedTime);
	}

	//-------------------------------------------------------------------------------------------
	void PauseCharacters()
	{
		bIsPaused = true;
		Pacman->Pause();
		Blinky->Pause();
		Inky->Pause();
		Pinky->Pause();
		Clyde->Pause();
	}

	//-------------------------------------------------------------------------------------------
	void UnPauseCharacters()
	{
		PauseTimer = 0.0f;
		bIsPaused = false;
		Pacman->UnPause();
		Blinky->UnPause();
		Inky->UnPause();
		Pinky->UnPause();
		Clyde->UnPause();
	}

	//-------------------------------------------------------------------------------------------
	void CheckCollision()
	{
		for(FGhost* Ghost: Ghosts)
		{
			//if they are both on the same tile...
			if(Maze->GetTile(Pacman->GetPosition()).TileID == Maze->GetTile(Ghost->GetPosition()).TileID)
			{
				//Eat ghost if possible...
				if(Ghost->IsFrightened())
				{
					Ghost->Die();
					const int Score = Pacman->GetScore();
					int ComboMeter = Pacman->GetComboMeter();
					Pacman->SetScore(Score + ComboMeter);
					ComboMeter *= 2;
					Pacman->SetComboMeter(ComboMeter);

					PauseCharacters();
				}
				//...kill pacman if not
				else if (!Ghost->IsDead())
				{
					Pacman->Die();
					bEnded = true;
				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void FrightenGhosts() const
	{
		for(FGhost* Ghost: Ghosts)
		{
			Ghost->Frighten();
		}
	}

	//-------------------------------------------------------------------------------------------
	void DrawScore()
	{
		DrawStringDecal(ScoreDrawPoint, std::to_string(Pacman->GetScore()));
	}

	//-------------------------------------------------------------------------------------------
	bool HasWon() const
	{
		return Maze->Pellets == 0;
	}

	//-------------------------------------------------------------------------------------------
	void EndGame(const bool bWon, const float ElapsedTime)
	{
		if(bWon)
		{
			//Display Win Screen
			Clear(olc::BLACK);
			DrawString(80, 110, "YOU WON!");
			DrawString(30, 118, "Press SPACE to exit.");
			DrawString(70, 142, "Score:");
			DrawString(80, 150, std::to_string(Pacman->GetScore()));
		}
		else
		{
			//Display Game Over Screen and animation
			GameOverTimer += ElapsedTime;
			Pacman->Update(ElapsedTime, RoundTime);
			if(GameOverTimer >= 3.0f)
			{
				Clear(olc::BLACK);
				DrawString(80, 110, "GAME OVER");
				DrawString(30, 118, "Press SPACE to exit.");
				DrawString(70, 142, "Score:");
				DrawString(80, 150, std::to_string(Pacman->GetScore()));
			}
		}
	}
	
};

int main()
{
	FPacMan Game;
	if (Game.Construct(224, 288, 3, 3))
		Game.Start();
	return 0;
}
