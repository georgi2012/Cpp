#pragma once
#include "Zoo.h"

class Planet {
private:
	Zoo* zoos;
	Fauna* faunas;

public:
	Planet(unsigned zooCapacity,unsigned faunaCapacity);
	~Planet();
	Planet(const Planet&) = delete;
	Planet& operator=(const Planet&) = delete;

	void addFamilyZoo(const Animal_Family& newFamily);
	void addFamilyZoo(const char* name, unsigned number);
	void addFamilyFauna(const Animal_Family& newFamily);
	void addFamilyFauna(const char* name, unsigned number);
	void removeFamilyZoo(const Animal_Family& newFamily);
	void removeFamilFauna(const Animal_Family& newFamily);
	void print(std::ostream& os) const ;

};