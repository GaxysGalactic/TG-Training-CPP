
/*
Exercise 2 - Military Clock

Create a class called MilitaryClock that stores and displays the military time.

Your class should contain the following constructors and methods:
MilitaryClock();
MilitaryClock(short hours, short minutes);
void SetTime(short hours, short minutes);
void DisplayTime();

Here’s an example of how the class could be used:
MilitaryClock clock;
clock.Display();
clock = MilitaryClock(7,0);
clock.Display();
clock.SetTime(12, 15);
clock.Display();

Don’t forget that military time is displayed as hhmm so add a preceding 0 before hours / minutes if their value is less than 10.

Example output
0000
0700
1215


*/


#include <iostream>


class MilitaryClock
{

private:

	short hours;
	short minutes;

public:

	MilitaryClock()
	{
		hours = 0;
		minutes = 0;
	}

	MilitaryClock(short pHours, short pMinutes)
	{
		hours = pHours;
		minutes = pMinutes;
	}

	void setTime(short pHours, short pMinutes)
	{
		hours = pHours;
		minutes = pMinutes;
	}

	void displayTime()
	{
		if (hours < 10)
		{
			std::cout << "0" << hours;
		}
		else
		{
			std::cout << hours;
		}

		if (minutes < 10)
		{
			std::cout << "0" << minutes;
		}
		else
		{
			std::cout << minutes;
		}
		std::cout << std::endl;
	}
};

int main()
{
	MilitaryClock clock;
	clock.displayTime();
	clock = MilitaryClock(7, 0);
	clock.displayTime();
	clock.setTime(12, 15);
	clock.displayTime();

}