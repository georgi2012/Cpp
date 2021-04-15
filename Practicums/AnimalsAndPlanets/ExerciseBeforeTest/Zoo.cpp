#include "Zoo.h"

Zoo::Zoo(unsigned int capacity):capacity(capacity)
{
	try {
		animalFamilies = new Animal_Family * [capacity];
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		animalFamilies = nullptr;
		return;
	}
}

Zoo::~Zoo()
{
	delete[] animalFamilies;
	numOfAnimals = numOfFamilies = 0;
}

void Zoo::addFamily(const char* name, unsigned number)
{
	if (numOfAnimals +number > capacity)
	{
		throw 0;
	}
	if (Fauna::findFamily(name, animalFamilies, numOfFamilies) > 0)
	{
		throw - 1;
	}
	Animal_Family* temp = new Animal_Family(name, number);
	animalFamilies[numOfFamilies++] = temp;
	temp = nullptr;
}

void Zoo::addFamily( Animal_Family& newFamily)
{
	addFamily(newFamily.getName(), newFamily.getNumber());

}

void Zoo::removeFamily(const char* name)
{
	int index = Fauna::findFamily(name, animalFamilies, numOfFamilies);
	if (index < 0)
	{
		return;
	}
	numOfAnimals -= animalFamilies[index]->getNumber();
	delete animalFamilies[index];
	animalFamilies[index] = animalFamilies[--numOfFamilies];
	animalFamilies[numOfFamilies] = nullptr;
}

void Zoo::removeFamily(const Animal_Family& newFamily)
{
	removeFamily(newFamily.getName());

}

void Zoo::print(std::ostream& os) const
{
	for (unsigned i = 0; i < numOfFamilies; i++)
	{
		animalFamilies[i]->print(os);
	}
}



