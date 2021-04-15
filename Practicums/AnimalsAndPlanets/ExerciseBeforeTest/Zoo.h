#pragma once
#include "Fauna.h"
class Zoo {
private:
	Animal_Family** animalFamilies = nullptr;
	const unsigned capacity = 0;
	unsigned numOfAnimals = 0;
	unsigned numOfFamilies = 0;

	//int findFamily(const char* name);

public:
	Zoo(unsigned int capacity);
	Zoo(const Zoo& ) = delete;
	Zoo& operator=(const Zoo&) = delete;
	~Zoo();

	void addFamily(const char* name, unsigned number);
	void addFamily( Animal_Family& newFamily);
	void removeFamily(const char* name);
	void removeFamily(const Animal_Family& newFamily);
	void print(std::ostream& os) const;
};