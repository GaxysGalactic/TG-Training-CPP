#include "Student.h"


//--------------------------------------------------------------
FStudent::FStudent()
{
	Name = nullptr;
	Age = 0;
}

//--------------------------------------------------------------
FStudent::FStudent(int InAge)
{
	Name = nullptr;
	Age = InAge;
}

//--------------------------------------------------------------
FStudent::~FStudent()
{
	delete Name;
}

//--------------------------------------------------------------
void FStudent::SetName(const char* NewName)
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

	Name = new char[NameLength + 1];
	memcpy_s(Name, sizeof(char) * (NameLength + 1), NewName, sizeof(char) * (NameLength + 1));
}

//--------------------------------------------------------------
void FStudent::SetAge(const int NewAge)
{
	Age = NewAge;
}

//--------------------------------------------------------------
void FStudent::Print()
{
	std::cout << "Name: " << Name << std::endl;
	std::cout << "Age: " << Age << std::endl;
}
