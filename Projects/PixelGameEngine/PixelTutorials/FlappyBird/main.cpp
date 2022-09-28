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

	class FBird
	{
	
	public:

		struct FCoord
		{
			float X = 0.0f;
			float Y = 0.0f;
		};


	};

private:
	float BirdPosition = 0.0f;
	float BirdVelocity = 0.0f;
	float BirdAcceleration = 0.0f;

	float Gravity = 800.0f;

	float SectionWidth;
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

		return true;
	}

	bool OnUserUpdate(float ElapsedTime) override
	{
		if (bResetGame)
		{
			bHasCollided = false;
			bResetGame = false;
			ListSection = { 0, 0, 0, 0 };
			BirdAcceleration = 0.0f;
			BirdVelocity = 0.0f;
			BirdPosition = ScreenHeight() / 2.0f;
			FlapCount = 0;
			++AttemptCount;
		}


		if (bHasCollided)
		{
			//Do nothing until user releases space
			if (GetKey(olc::Key::SPACE).bReleased)
			{
				bResetGame = true;
			}
		}
		else
		{

			if (GetKey(olc::Key::SPACE).bPressed)
			{
				BirdAcceleration = 0.0f;
				BirdVelocity = -Gravity / 6.0f;
				++FlapCount;
				if (FlapCount > MaxFlapCount)
				{
					MaxFlapCount = FlapCount;
				}
			}
			else
			{
				BirdAcceleration += Gravity * ElapsedTime;
			}

			if (BirdAcceleration >= Gravity)
			{
				BirdAcceleration = Gravity;
			}


			BirdVelocity += BirdAcceleration * ElapsedTime;
			BirdPosition += BirdVelocity * ElapsedTime;

			int BirdX = (int)(ScreenWidth() / 3.0f);

			LevelPosition += 14.0 * 8 * ElapsedTime;

			if (LevelPosition > SectionWidth)
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

			FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

			int Section = 0;
			for (int s : ListSection)
			{
				if (s != 0)
				{
					int SectionStart = Section * SectionWidth;
					int Offset = 0.25f * SectionWidth;
					int GapSize = 0.4f * SectionWidth;

					int RectangleWidth = SectionWidth / 4;
					int RectangleStartX = SectionStart + Offset - LevelPosition;
					int RectangleEndX = RectangleStartX + RectangleWidth;

					int LowerRectangleStartY = ScreenHeight() - s;
					int UpperRectangleHeight = ScreenHeight() - s - GapSize;

					FillRect(
						RectangleStartX,
						LowerRectangleStartY,
						RectangleWidth,
						ScreenHeight(),
						olc::GREEN);
					FillRect(
						RectangleStartX,
						0,
						RectangleWidth,
						UpperRectangleHeight,
						olc::GREEN);

					if (Section == 1)
					{
						bHasCollided =
							//Upper Left Pixel
							BirdPosition < 16
							|| (BirdPosition < UpperRectangleHeight&& BirdX > RectangleStartX && BirdX < RectangleEndX)
							//Lower Left Pixel
							|| BirdPosition + 16 > ScreenHeight()
							|| (BirdPosition + 16 > LowerRectangleStartY && BirdX > RectangleStartX && BirdX < RectangleEndX)
							//Upper Right Pixel
							|| (BirdPosition < UpperRectangleHeight&& BirdX + 48 > RectangleStartX && BirdX + 48 < RectangleEndX)
							//Lower Right Pixel
							|| (BirdPosition + 16 > LowerRectangleStartY && BirdX + 48 > RectangleStartX && BirdX + 48 < RectangleEndX);
					}

				}
				Section++;
			}

			/*Collision Detection
			bHasCollided =
				BirdPosition < 2
				|| BirdPosition > ScreenHeight()
				|| (BirdPosition > LowerRectangleStartY && BirdX > RectangleStartX && BirdX < RectangleEndX)
				|| (BirdPosition < UpperRectangleHeight && BirdX > RectangleStartX && BirdX < RectangleEndX)*/


			// Draw Bird
			if (BirdVelocity > 0)
			{
				DrawString(BirdX, BirdPosition, "\\\\\\");
				DrawString(BirdX, BirdPosition + 8, "<\\\\\\=Q");
			}
			else
			{
				DrawString(BirdX, BirdPosition, "<///=Q");
				DrawString(BirdX, BirdPosition + 8, "///");
			}

			DrawString(1, 1, "Attempt: " + std::to_string(AttemptCount) + " Score: " + std::to_string(FlapCount) + " High Score: " + std::to_string(MaxFlapCount));
			
		}

		return true;
	}
};

int main()
{
	FFlappyBird Game;
	if (Game.Construct(720, 350, 2, 2))
		Game.Start();
	return 0;
}
