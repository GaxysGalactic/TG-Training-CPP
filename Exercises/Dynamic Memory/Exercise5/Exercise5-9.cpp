/*
* We’ve created an important problem in the previous exercise. We managed to save memory by
* a
*/


#include <iostream>
#include <string>

class FStudent
{

private:
	char* Name;
	int Age;

public:
	
	//--------------------------------------------------------------
	FStudent()
	{
		Name = nullptr;
		Age = 0;
	}

	//--------------------------------------------------------------
	FStudent(int InAge)
	{
		Name = nullptr;
		Age = InAge;
	}

	//--------------------------------------------------------------
	~FStudent()
	{
		delete Name;
	}

	//--------------------------------------------------------------
	void SetName(const char* NewName)
	{
		if (Name)
		{
			delete Name;
			Name = nullptr;
		}

		int NameLength = 0;
		for (int i = 0; NewName[i] != '\0'; i++)
		{
			NameLength++;
		}

		Name = new char[NameLength+1];
		memcpy_s(Name, sizeof(char) * (NameLength+1), NewName, sizeof(char) * (NameLength+1));
	}

	//--------------------------------------------------------------
	void Print()
	{
		std::cout << "Name: " << Name << std::endl;
		std::cout << "Age: " << Age << std::endl;
	}
};



int main()
{
	//-------- Test ----

	FStudent* StudentTest = new FStudent(8);
	StudentTest -> SetName("Chavito"); 

	delete StudentTest;

	std::cout << "On this first test, the Student gets deleted from memory, but the name remains." << std::endl;
	std::cout << "This is because the class Student tries to call the destructor for all its members to free the memory, but Name is a primitive type." << std::endl;
	std::cout << "Therefore, it does not get deleted automatically." << std::endl;

	//------------------

	std::cout << "How many students do you want? " << std::endl;

	int NumberOfStudents;
	std::cin >> NumberOfStudents;

	FStudent* Students = new FStudent[NumberOfStudents];

	std::cout << "You now have " << NumberOfStudents << " students!" << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Enter a name for student #" << i + 1 << ": ";
		char Name[32];
		std::cin >> Name;

		std::cout << "Enter the age for student #" << i+1 << ": ";
		int Age;
		std::cin >> Age;

		FStudent Student = FStudent(Age);
		Student.SetName(Name);
		Students[i] = Student;
	}


	std::cout << "Here are your students:" << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Student " << i+1 << std::endl;
		Students[i].Print();
	}


	delete[] Students;
}