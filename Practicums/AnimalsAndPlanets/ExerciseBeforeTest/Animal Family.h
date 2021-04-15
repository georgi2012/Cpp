#pragma once
#include <iostream>

class Animal_Family {
private:

	char* name=nullptr;
	unsigned int number=0;

	void copyFrom(const Animal_Family& other);
public:
	//Animal_Family()
	Animal_Family(const char* newName, unsigned int newNum);
	Animal_Family(const Animal_Family& other);
	Animal_Family& operator=(const Animal_Family& other);

	~Animal_Family();

	const char* getName() const;
	unsigned int getNumber() const;
	void print(std::ostream& os) const;

};