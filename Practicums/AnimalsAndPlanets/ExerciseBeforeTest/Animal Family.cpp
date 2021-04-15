
#include <cstring>
#include "Animal Family.h"


void Animal_Family::copyFrom(const Animal_Family& other)
{//strong exeption guarantee!!!
	char* newName = nullptr;//new char[strlen(other.name)];
	try {
		newName = new char[strlen(other.name)];
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		return;
	}
	delete[] name;
	strcpy_s(newName, strlen(other.name),other.name);
	name = newName;
	number = other.number;
	newName = nullptr;
	
}

Animal_Family::Animal_Family(const char* newName, unsigned int newNum)
{
	std::cout << "Animal Created\n";
	try {
		name = new char [strlen(newName)+1];
	}
	catch (const std::exception &e)
	{
		std::cerr << "Memory allocation error "<<e.what()<<std::endl;
		return;
	}
	strcpy_s(name, strlen(newName)+1, newName);
	//strcpy(name, newName);
	number = newNum;

}

Animal_Family::Animal_Family(const Animal_Family& other)
{
	copyFrom(other);
}

Animal_Family& Animal_Family::operator=(const Animal_Family& other)
{
	
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

Animal_Family::~Animal_Family()
{
	delete[] name;
	number = 0;
	name = nullptr;

}

const char* Animal_Family::getName() const
{
	return name;
}

unsigned int Animal_Family::getNumber() const
{
	return number;
}

void Animal_Family::print(std::ostream& os) const
{
	os << "Name :" << name << " , Number of members: " << number << std::endl;
}
