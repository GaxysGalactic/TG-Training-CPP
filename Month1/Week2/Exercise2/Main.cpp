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