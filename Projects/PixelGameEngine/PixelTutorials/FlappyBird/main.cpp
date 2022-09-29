#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class FFlappyBird : public olc::PixelGameEngine
{
public:
	FFlappyBird()
	{
		// Name your application
		sAppName = "Flappy Bird";
	}

private:

	class FBird
	{
	public:

		struct FCoord
		{
			float X = 0.0f;
			float Y = 0.0f;
		};

		float Position = 0.0f;
		float Velocity = 0.0f;
		float Acceleration = 0.0f;

		float DrawPoint = 0.0f;

		float BirdWidth = 0.0f;
		float BirdLength = 0.0f;

		FCoord UpperLeft;
		FCoord UpperRight;
		FCoord LowerLeft;
		FCoord LowerRight;

		FBird()
		{

		}

		FBird(const float& InDrawPoint, const float& InBirdWidth, const float& InBirdLength)
		{
			DrawPoint = InDrawPoint;
			BirdWidth = InBirdWidth;
			BirdLength = InBirdLength;

			UpperLeft.X = DrawPoint;
			UpperLeft.Y = Position;

			UpperRight.X = DrawPoint + BirdWidth;
			UpperRight.Y = Position;

			LowerLeft.X = DrawPoint;
			LowerLeft.Y = Position + BirdLength;

			LowerRight.X = DrawPoint + BirdWidth;
			LowerRight.Y = Position + BirdLength;
		}

		void UpdateCoords()
		{
			UpperLeft.Y = Position;
			UpperRight.Y = Position;
			LowerLeft.Y = Position + BirdLength;
			LowerRight.Y = Position + BirdLength;
		}

		bool Collides(const float& UpperRectangleHeight, const float& LowerRectangleStartY, const float& RectangleStartX, const float& RectangleEndX)
		{
			return
				//Upper Left Pixel
				(UpperLeft.Y < UpperRectangleHeight
				&& UpperLeft.X > RectangleStartX
				&& UpperLeft.X < RectangleEndX)
				//Lower Left Pixel
				|| (LowerLeft.Y > LowerRectangleStartY
					&& LowerLeft.X > RectangleStartX
					&& LowerLeft.X < RectangleEndX)
				//Upper Right Pixel
				|| (UpperRight.Y < UpperRectangleHeight
					&& UpperRight.X > RectangleStartX
					&& UpperRight.X < RectangleEndX)
				//Lower Right Pixel
				|| (LowerRight.Y > LowerRectangleStartY
					&& LowerRight.X > RectangleStartX
					&& LowerRight.X < RectangleEndX);
		}
	};

	FBird* Bird;

	const float Gravity = 800.0f;

	float SectionWidth;
	int SectionOffset;
	int GapSize;
	int RectangleWidth;

	std::list<int> ListSection;
	float LevelPosition = 0.0f;

	bool bHasCollided = false;

	int AttemptCount = 0;
	int FlapCount = 0;
	int MaxFlapCount = 0;

	bool bResetGame = true;

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		ListSection = { 0, 0, 0, 0 };
		SectionWidth = (float)ScreenWidth() / (float)(ListSection.size() - 1);
		SectionOffset = 0.25f * SectionWidth;
		GapSize = 0.4f * SectionWidth;
		RectangleWidth = SectionWidth / 4;

		Bird = new FBird((ScreenWidth() / 3.0f), 48, 16);

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		// Reset Game
		if (bResetGame)
		{
			ResetGame();
		}

		//End Game?
		if (bHasCollided)
		{
			EndGame();
		}
		else
		{
			//Update Game Physics
			UpdatePhysics(ElapsedTime);

			//Create New Section if needed
			if (LevelPosition > SectionWidth)
			{
				CreateNewSection();
			}

			//Clear Screen
			FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(131, 174, 242));


			//Draw Level
			DrawLevel();


			// Draw Bird
			DrawBird();

			//Draw Score
			DrawString(1, 1, "Attempt: " + std::to_string(AttemptCount) + " Score: " + std::to_string(FlapCount) + " High Score: " + std::to_string(MaxFlapCount));
			
		}

		return true;
	}

	bool OnUserDestroy() override
	{
		delete Bird;
		return true;
	}

private:

	void ResetGame()
	{
		bHasCollided = false;
		bResetGame = false;
		ListSection = { 0, 0, 0, 0 };
		Bird->Acceleration = 0.0f;
		Bird->Velocity = 0.0f;
		Bird->Position = ScreenHeight() / 2.0f;
		Bird->UpdateCoords();
		FlapCount = 0;
		++AttemptCount;
	}

	void EndGame()
	{
		//Do nothing until user releases space
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			bResetGame = true;
		}
	}

	void UpdatePhysics(const float ElapsedTime)
	{
		if (GetKey(olc::Key::SPACE).bPressed)
		{
			Bird->Acceleration = 0.0f;
			Bird->Velocity = -Gravity / 6.0f;
			++FlapCount;
			if (FlapCount > MaxFlapCount)
			{
				MaxFlapCount = FlapCount;
			}
		}
		else
		{
			Bird->Acceleration += Gravity * ElapsedTime;
		}

		if (Bird->Acceleration >= Gravity)
		{
			Bird->Acceleration = Gravity;
		}

		Bird->Velocity += Bird->Acceleration * ElapsedTime;
		Bird->Position += Bird->Velocity * ElapsedTime;
		Bird->UpdateCoords();

		LevelPosition += 14.0 * 8 * ElapsedTime;
	}

	void CreateNewSection()
	{
		LevelPosition -= SectionWidth;
		ListSection.pop_front();
		int i = std::rand() % (int)(ScreenHeight() * 0.8);
		if (0.85f * ScreenHeight() <= i && i <= 0.15f * ScreenHeight())
		{
			i = 0;
		}
		ListSection.push_back(i);
	}

	void DrawLevel()
	{
		int Section = 0;
		for (int s : ListSection)
		{
			if (s != 0)
			{
				int SectionStart = Section * SectionWidth;
				
				int RectangleStartX = SectionStart + SectionOffset - LevelPosition;
				int RectangleEndX = RectangleStartX + RectangleWidth;

				int LowerRectangleStartY = ScreenHeight() - s;
				int UpperRectangleHeight = ScreenHeight() - s - GapSize;

				//Lower Rectangle
				FillRect(
					RectangleStartX,
					LowerRectangleStartY,
					RectangleWidth,
					ScreenHeight() - LowerRectangleStartY,
					olc::GREEN);

				//Upper Rectangle
				FillRect(
					RectangleStartX,
					0,
					RectangleWidth,
					UpperRectangleHeight,
					olc::GREEN);

				//Handle Collision
				if (Section == 1)
				{
					bHasCollided =
						//Top & Bottom
						Bird->UpperLeft.Y < 0
						|| Bird->LowerLeft.Y > ScreenHeight()
						//Rectangles
						|| Bird->Collides(UpperRectangleHeight, LowerRectangleStartY, RectangleStartX, RectangleEndX);
				}

			}
			Section++;
		}
	}

	void DrawBird()
	{
		if (Bird->Velocity > 0)
		{
			DrawString(Bird->DrawPoint, Bird->Position, "\\\\\\");
			DrawString(Bird->DrawPoint, Bird->Position + 8, "<\\\\\\=Q");
		}
		else
		{
			DrawString(Bird->DrawPoint, Bird->Position, "<///=Q");
			DrawString(Bird->DrawPoint, Bird->Position + 8, "///");
		}
	}
};

int main()
{
	FFlappyBird Game;
	if (Game.Construct(720, 350, 2, 2))
		Game.Start();
	return 0;
}
