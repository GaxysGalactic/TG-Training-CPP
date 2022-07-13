#include <iostream>

int main()
{
	enum Prediction
	{
		PredictionPositive, PredictionNegative, PredictionMaybe, PredictionAskAgain, Prediction42,
	};

	std::cout << "Welcome to your future! Please ask a question: ";
	std::string question;
	std::cin >> question;

	std::srand(std::time(0));

	int computerChoice = std::rand() % 5;

	std::cout << "Your answer is: ";

	switch (computerChoice)
	{
		case PredictionPositive:
			std::cout << "Almost certainly." << std::endl;
			break;
		case PredictionNegative:
			std::cout << "Negative, chief." << std::endl;
			break;
		case PredictionMaybe:
			std::cout << "Theres a chance it could happen." << std::endl;
			break;
		case PredictionAskAgain:
			std::cout << "Yes, no, maybe....I don't know, can you repeat the question?" << std::endl;
			break;
		case Prediction42:
			std::cout << "42." << std::endl;
			break;
	}
}