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
	SpaceObject Player;

public:

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		Asteroids.push_back({ 20.0f, 20.0f, 8.0f, -6.0f, (int)16, 0.0f});

		//Initialize Player Position
		Player.X = ScreenWidth() / 2.0f;
		Player.Y = ScreenHeight() / 2.0f;
		Player.dX = 0.0f;
		Player.dY = 0.0f;
		Player.Angle = 0.0f;

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		//Clear Screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		//Steer
		if (GetKey(olc::Key::LEFT).bHeld)
		{
			Player.Angle -= 5.0f * ElapsedTime;
		}
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			Player.Angle += 5.0f * ElapsedTime;
		}

		//Thrust
		if (GetKey(olc::Key::UP).bHeld)
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

		//Update and Draw Asteroids
		for (auto& a : Asteroids)
		{
			a.X += a.dX * ElapsedTime;
			a.Y += a.dY * ElapsedTime;
			WrapCoordinates(a.X, a.Y, a.X, a.Y);

			for (int x = 0; x < a.Size; x++)
			{
				for (int y = 0; y < a.Size; y++)
				{
					Draw(a.X + x, a.Y + y, olc::RED);
				}
			}
		}

		//Draw Ship
		float MX[3] = { 0.0f, -2.5f, 2.5f }; // Ship Model Vertices
		float MY[3] = { -5.5f, 2.5f, 2.5f };

		float SX[3];
		float SY[3];

		//Rotate
		for (int i = 0; i < 3; i++)
		{
			SX[i] = MX[i] * cosf(Player.Angle) - MY[i] * sinf(Player.Angle);
			SY[i] = MX[i] * sinf(Player.Angle) + MY[i] * cosf(Player.Angle);
		}

		// Translate
		for (int i = 0; i < 3; i++)
		{
			SX[i] = SX[i] + Player.X;
			SY[i] = SY[i] + Player.Y;
		}

		//Draw Closed Polygon
		for (int i = 0; i < 4; i++)
		{
			int j = i + 1;
			DrawLine(SX[i % 3], SY[i % 3], SX[j % 3], SY[j % 3]);
		}

		return true;
	}

private:

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
		int verts = ModelCoordinates.size();
		TransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++)
		{
			TransformedCoordinates[i].first = ModelCoordinates[i].first * cosf(R) - ModelCoordinates[i].second * sinf(R);
			TransformedCoordinates[i].second = ModelCoordinates[i].first * sinf(R) + ModelCoordinates[i].second * cosf(R);
		}

		// Scale
		for (int i = 0; i < verts; i++)
		{
			TransformedCoordinates[i].first = TransformedCoordinates[i].first * S;
			TransformedCoordinates[i].second = TransformedCoordinates[i].second * S;
		}

		// Translate
		for (int i = 0; i < verts; i++)
		{
			TransformedCoordinates[i].first = TransformedCoordinates[i].first + X;
			TransformedCoordinates[i].second = TransformedCoordinates[i].second + Y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine(TransformedCoordinates[i % verts].first, TransformedCoordinates[i % verts].second,
				TransformedCoordinates[j % verts].first, TransformedCoordinates[j % verts].second, p);
		}
	}

};

int main()
{
	AsteroidsGame Game;
	if (Game.Construct(256, 240, 4, 4))
	{
		Game.Start();
	}
	return 0;
}