#pragma once
#include "Animal Family.h"


class Fauna {
private:
	Animal_Family** animalFamilies=nullptr;
	const unsigned capacity=0; //max number of animals
	unsigned numOfAnimals = 0;
	unsigned numOfFamilies = 0;

	static int findFamily(const char* name, Animal_Family** family, unsigned numOfFamilies);

public:

	Fauna(const unsigned capacity);
	Fauna(const Fauna& other);
	~Fauna();
	void addFamily(const char* name, unsigned number);
	void addFamily(const Animal_Family& newFamily);
	void removeFamily(const char* name);
	void removeFamily(const Animal_Family& newFamily);
	void print(std::ostream& os) const;

	friend class Zoo;
};