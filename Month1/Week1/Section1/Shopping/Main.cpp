#include <iostream>

int main()
{
	int lampOilPrice = 15;
	int ropePrice = 6;
	int bombsPrice = 10;

	std::cout << "Welcome to Morshu's!" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Bombs: " << bombsPrice << " gold each" << std::endl;
	std::cout << "Ropes: " << ropePrice << " gold each" << std::endl;
	std::cout << "Lamp Oil: " << lampOilPrice << " gold each" << std::endl;
	
	float lampOil;
	int rope, bombs;

	std::cout << "How many bombs do you want?" << std::endl;
	std::cin >> bombs;

	std::cout << "How many ropes do you want? " << std::endl;
	std::cin >> rope;

	std::cout << "How much lamp oil do you want?" << std::endl;
	std::cin >> lampOil;


	float totalLampOil = lampOil * lampOilPrice;
	int totalRope = rope * ropePrice;
	int totalBombs = bombs * bombsPrice;

	std::cout << bombs << " bombs: " << totalBombs << std::endl;
	std::cout << rope << " ropes: " << totalRope << std::endl;
	std::cout << lampOil << " ounces of lamp oil: " << totalLampOil << std::endl;

	float total = totalLampOil + totalBombs + totalRope;

	std::cout << "Your total cost was " << total << " gold!" << std::endl;
}