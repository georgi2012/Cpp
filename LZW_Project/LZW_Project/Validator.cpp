#include "Validator.h"

inline void Validator::addToSum(const uint32_t num)
{
	checksum = (checksum + num * CHECK_MULTY) % CHECK_MOD;
}

inline void Validator::resetSum()
{
	checksum = 0;
}

uint32_t Validator::getSum() const
{
	return checksum;
}

bool Validator::isValid(ifstream& input, const uint32_t C_END)
{//Starts from code part
	resetSum();
	uint32_t code = 0;
	while (input.read((char*)&code, sizeof(uint32_t)) &&
		code != C_END) {//we take the code that have been in the table
		addToSum(code);
	}
	input.read((char*)&code, sizeof(uint32_t)); //get checksum encoded at the end of the file
	return code == checksum;
}
