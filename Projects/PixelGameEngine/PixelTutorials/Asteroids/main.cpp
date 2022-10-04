#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class AsteroidsGame : public olc::PixelGameEngine
{
public:

	AsteroidsGame()
	{
		// Name your application
		sAppName = "Asteroids";
	}

private:

	struct SpaceObject
	{
		float X;
		float Y;
		float dX;
		float dY;
		int Size;
		float Angle;
	};

	std::vector<SpaceObject> Asteroids;
	std::vector<SpaceObject> Bullets;
	SpaceObject Player;
	int Score = 0;
	bool bDead = false;

	std::vector<std::pair<float, float>> ModelShip;
	std::vector<std::pair<float, float>> ModelAsteroid;

public:

	bool OnUserCreate() override
	{

		//Initialize Models
		InitializeModels();

		//Set Variables
		ResetGame();

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		//Reset Game?
		if (bDead)
		{
			ResetGame();
		}

		//Clear Screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		//Control Ship
		UpdateShipPhysics(ElapsedTime);

		//Update and Draw Asteroids
		DrawAsteroids(ElapsedTime);

		//Update and Draw Bullets
		DrawBullets(ElapsedTime);

		//Remove Trash
		RemoveExtraEntities();

		//WinGame
		if (Asteroids.empty())
		{
			WinGame();
		}

		//Draw Ship
		DrawWireFrameModel(ModelShip, Player.X, Player.Y, Player.Angle);

		//Draw Score
		DrawString(2, 2, "SCORE: " + std::to_string(Score));


		return true;
	}

private:

	void InitializeModels()
	{
		ModelShip =
		{
			{ 0.0f, -5.0f },
			{ -2.5f, 2.5f },
			{ 2.5f, 2.5f }
		};  //A simple Isosceles Triangle

		int Verts = 20;
		for (int i = 0; i < Verts; i++)
		{
			float Radius = (float)std::rand() / (float)RAND_MAX * 0.4f + 0.8f;
			float a = ((float)i / (float)Verts) * 6.28318f;
			ModelAsteroid.push_back(std::make_pair(Radius * sinf(a), Radius * cosf(a)));
		}
	}

	void UpdateShipPhysics(float& ElapsedTime)
	{
		//Steer
		if (GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::A).bHeld)
		{
			Player.Angle -= 5.0f * ElapsedTime;
		}
		if (GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::D).bHeld)
		{
			Player.Angle += 5.0f * ElapsedTime;
		}

		//Thrust
		if (GetKey(olc::Key::UP).bHeld || GetKey(olc::Key::W).bHeld)
		{
			//ACCELERATION changes VELOCITY (w.r.t. Time)
			Player.dX += sin(Player.Angle) * 20.0f * ElapsedTime;
			Player.dY += -cos(Player.Angle) * 20.0f * ElapsedTime;
		}

		//VELOCITY changes POSITION (w.r.t. Time)
		Player.X += Player.dX * ElapsedTime;
		Player.Y += Player.dY * ElapsedTime;

		//Keep Ship in Gamespace
		WrapCoordinates(Player.X, Player.Y, Player.X, Player.Y);

		//Check ship collision with asteroids
		for (SpaceObject& a : Asteroids)
		{
			if (IsPointInsideCircle(a.X, a.Y, a.Size, Player.X, Player.Y))
			{
				bDead = true;
			}
		}
	}

	void DrawAsteroids(float& ElapsedTime)
	{
		for (SpaceObject& a : Asteroids)
		{
			a.X += a.dX * ElapsedTime;
			a.Y += a.dY * ElapsedTime;
			a.Angle += 0.5f * ElapsedTime;

			WrapCoordinates(a.X, a.Y, a.X, a.Y);

			DrawWireFrameModel(ModelAsteroid, a.X, a.Y, a.Angle, a.Size, olc::YELLOW);
		}
	}

	void DrawBullets(float& ElapsedTime)
	{
		//FireBullet in direction of player
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			Bullets.push_back({ Player.X, Player.Y, 50.0f * sinf(Player.Angle), -50.0f * cosf(Player.Angle), 100 });
		}

		std::vector<SpaceObject> NewAsteroids;

		//Update and Draw Bullets
		for (SpaceObject& b : Bullets)
		{
			b.X += b.dX * ElapsedTime;
			b.Y += b.dY * ElapsedTime;
			WrapCoordinates(b.X, b.Y, b.X, b.Y);

			//Check Collision with Asteroids
			for (SpaceObject& a : Asteroids)
			{
				if (IsPointInsideCircle(a.X, a.Y, a.Size, b.X, b.Y))
				{
					//Asteroid Hit
					b.X = -100;

					if (a.Size > 4)
					{
						//Create two child asteroids
						float Angle1 = ((float)std::rand() / (float)RAND_MAX) * 6.283185f;
						float Angle2 = ((float)std::rand() / (float)RAND_MAX) * 6.283185f;

						NewAsteroids.push_back({ a.X, a.Y, 10.0f * sinf(Angle1), 10.0f * cosf(Angle1), (int)a.Size >> 1, 0.0f });
						NewAsteroids.push_back({ a.X, a.Y, 10.0f * sinf(Angle2), 10.0f * cosf(Angle2), (int)a.Size >> 1, 0.0f });

					}

					a.X = -100;
					Score += 100;
				}
			}

			Draw(b.X, b.Y);
		}

		//Append new asteroids to existing vector
		for (SpaceObject& a : NewAsteroids)
		{
			Asteroids.push_back(a);
		}
	}

	void RemoveExtraEntities()
	{
		//Remove off screen bullets
		if (Bullets.size() > 0)
		{
			auto i = std::remove_if(Bullets.begin(), Bullets.end(), [&](SpaceObject o) {return (o.X < 1 || o.Y < 1 || o.X >= ScreenWidth() || o.Y >= ScreenHeight()); });

			if (i != Bullets.end())
			{
				Bullets.erase(i);
			}
		}

		//Remove blown up asteroids
		if (Asteroids.size() > 0)
		{
			auto i = std::remove_if(Asteroids.begin(), Asteroids.end(), [&](SpaceObject o) { return (o.X < 0); });

			if (i != Asteroids.end())
			{
				Asteroids.erase(i);
			}
		}
	}

	void WinGame()
	{
		//Level Clear
		Score += 1000;
		Asteroids.clear();
		Bullets.clear();

		// Add two new asteroids, but in a place where the player is not, we'll simply
		// add them 90 degrees left and right to the player, their coordinates will
		// be wrapped by the next asteroid update
		Asteroids.push_back({ 30.0f * sinf(Player.Angle - 3.14159f / 2.0f) + Player.X,
										  30.0f * cosf(Player.Angle - 3.14159f / 2.0f) + Player.Y,
										  10.0f * sinf(Player.Angle), 10.0f * cosf(Player.Angle), (int)16, 0.0f });

		Asteroids.push_back({ 30.0f * sinf(Player.Angle + 3.14159f / 2.0f) + Player.X,
										  30.0f * cosf(Player.Angle + 3.14159f / 2.0f) + Player.Y,
										  10.0f * sinf(-Player.Angle), 10.0f * cosf(-Player.Angle), (int)16, 0.0f });
	}

	void WrapCoordinates(float IX, float IY, float& OX, float& OY)
	{
		OX = IX;
		OY = IY;

		if (IX < 0.0f)
		{
			OX = IX + (float)ScreenWidth();
		}
		if (IX >= (float)ScreenWidth())
		{
			OX = IX - (float)ScreenWidth();
		}

		if (IY < 0.0f)
		{
			OY = IY + (float)ScreenHeight();
		}
		if (IY >= (float)ScreenHeight())
		{
			OY = IY - (float)ScreenHeight();
		}
	}

	virtual bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE)
	{
		float X;
		float Y;
		WrapCoordinates(x, y, X, Y);
		return olc::PixelGameEngine::Draw(X, Y, p);
	}

	void DrawWireFrameModel(const std::vector<std::pair<float, float>>& ModelCoordinates, float X, float Y, float R = 0.0f, float S = 1.0f, olc::Pixel p = olc::WHITE)
	{
		// pair.first = x coordinate
		// pair.second = y coordinate

		// Create translated model vector of coordinate pairs
		std::vector<std::pair<float, float>> TransformedCoordinates;
		int Verts = ModelCoordinates.size();
		TransformedCoordinates.resize(Verts);

		// Rotate
		for (int i = 0; i < Verts; i++)
		{
			TransformedCoordinates[i].first = ModelCoordinates[i].first * cosf(R) - ModelCoordinates[i].second * sinf(R);
			TransformedCoordinates[i].second = ModelCoordinates[i].first * sinf(R) + ModelCoordinates[i].second * cosf(R);
		}

		// Scale
		for (int i = 0; i < Verts; i++)
		{
			TransformedCoordinates[i].first = TransformedCoordinates[i].first * S;
			TransformedCoordinates[i].second = TransformedCoordinates[i].second * S;
		}

		// Translate
		for (int i = 0; i < Verts; i++)
		{
			TransformedCoordinates[i].first = TransformedCoordinates[i].first + X;
			TransformedCoordinates[i].second = TransformedCoordinates[i].second + Y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < Verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine(TransformedCoordinates[i % Verts].first, TransformedCoordinates[i % Verts].second,
				TransformedCoordinates[j % Verts].first, TransformedCoordinates[j % Verts].second, p);
		}
	}

	bool IsPointInsideCircle(float CX, float CY, float Radius, float X, float Y)
	{
		return sqrt((X - CX) * (X - CX) + (Y - CY) * (Y - CY)) < Radius;
	}

	void ResetGame()
	{
		Asteroids.clear();
		Bullets.clear();

		Asteroids.push_back({ 20.0f, 20.0f, 8.0f, -6.0f, (int)16, 0.0f });
		Asteroids.push_back({ 100.0f, 20.0f, -5.0f, 3.0f, (int)16, 0.0f });

		//Initialize Player Position
		Player.X = ScreenWidth() / 2.0f;
		Player.Y = ScreenHeight() / 2.0f;
		Player.dX = 0.0f;
		Player.dY = 0.0f;
		Player.Angle = 0.0f;

		bDead = false;
		Score = 0;
	}



};

int main()
{
	AsteroidsGame Game;
	if (Game.Construct(128, 120, 4, 4))
	{
		Game.Start();
	}
	return 0;
}