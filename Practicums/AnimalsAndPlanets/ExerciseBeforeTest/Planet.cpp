#include "Planet.h"

Planet::Planet(unsigned zooCapacity, unsigned faunaCapacity)
{
	zoos = new Zoo(zooCapacity);
	faunas = new Fauna(faunaCapacity);
}

Planet::~Planet()
{
	delete zoos;
	delete faunas;
}

void Planet::addFamilyZoo(const Animal_Family& newFamily)
{

	zoos->addFamily(newFamily.getName(),newFamily.getNumber());
}

void Planet::addFamilyZoo(const char* name, unsigned number)
{
	zoos->addFamily(name, number);
}

void Planet::addFamilyFauna(const Animal_Family& newFamily)
{
	faunas->addFamily(newFamily.getName(), newFamily.getNumber());
}

void Planet::addFamilyFauna(const char* name, unsigned number)
{
	faunas->addFamily(name, number);
}

void Planet::removeFamilyZoo(const Animal_Family& newFamily)
{
	zoos->removeFamily(newFamily.getName());
}

void Planet::removeFamilFauna(const Animal_Family& newFamily)
{
	faunas->removeFamily(newFamily.getName());
}

void Planet::print(std::ostream& os) const
{
	os << "Animals is cages:\n";
	zoos->print(os);
	os << "Free animals:\n";
	faunas->print(os);
}
