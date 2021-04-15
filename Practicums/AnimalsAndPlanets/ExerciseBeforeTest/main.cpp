#include "Planet.h"


int main()
{
	Planet planet(20,20);
	planet.addFamilyFauna(Animal_Family("Cats", 5));
	planet.addFamilyZoo("Dogs", 10);
	planet.addFamilyFauna("Birds", 3);
	planet.print(std::cout);

	return 0;
}