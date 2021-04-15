#include "Fauna.h"
//#include <exeption>
#include <cstring>

int Fauna::findFamily(const char* name,Animal_Family** family,unsigned numOfFamilies)
{
	for (unsigned i = 0; i < numOfFamilies; i++)
	{
		if (strcmp(family[i]->getName(), name) == 0)
		{
			return i;
		}
	}
	return -1;

}

Fauna::Fauna(const unsigned capacity) :capacity(capacity)
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

Fauna::Fauna(const Fauna& other):capacity(other.capacity)
,numOfAnimals(other.numOfAnimals)
,numOfFamilies(other.numOfFamilies)
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
	for (unsigned i = 0; i < numOfFamilies; i++)
	{
		animalFamilies[i] = new Animal_Family(*other.animalFamilies[i]);
	}


}

Fauna::~Fauna()
{
	for (unsigned i = 0; i < numOfFamilies; i++)
	{
		delete animalFamilies[i];
	}
	delete[] animalFamilies;
	numOfAnimals = numOfFamilies = 0;
}

void Fauna::addFamily(const char* name, unsigned number)
{
	if (findFamily(name,animalFamilies,numOfFamilies) > 0)
	{
		throw std::exception("There is such family in the fauna already");
	}
	if (capacity < number + numOfAnimals)
	{
		throw std::exception("There is not enough space in the fauna");
	}
	animalFamilies[numOfFamilies++] = new Animal_Family(name, number);
	numOfAnimals += number;
}

void Fauna::addFamily(const Animal_Family& newFamily)
{
	/*if (findFamily(newFamily.getName(),animalFamilies,numOfFamilies) < 0)
	{
		throw std::exception("There is such family in the fauna already");
	}
	if (capacity < newFamily.getNumber() + numOfAnimals)
	{
		throw std::exception("There is not enough space in the fauna");
	}
	animalFamilies[numOfFamilies++] = new Animal_Family(newFamily.getName(), newFamily.getNumber());
	numOfAnimals += newFamily.getNumber();*/
	addFamily(newFamily.getName(), newFamily.getNumber());
}

void Fauna::removeFamily(const char* name)
{
	int foundFamilyIndex = findFamily(name,animalFamilies,numOfFamilies);
	if (foundFamilyIndex < 0)
	{
		return;
	}

	Animal_Family* temp = animalFamilies[foundFamilyIndex];
	animalFamilies[foundFamilyIndex] = animalFamilies[numOfFamilies - 1];
	animalFamilies[--numOfFamilies] = nullptr;
	numOfAnimals -= temp->getNumber();
	delete temp;

}

void Fauna::removeFamily(const Animal_Family& newFamily)
{
	removeFamily(newFamily.getName());
}

void Fauna::print(std::ostream& os) const
{
	for (unsigned i = 0; i < numOfFamilies; i++)
	{
		animalFamilies[i]->print(os);
	}
}

