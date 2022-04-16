#pragma once
#include <cstdint>//fixed int size
#include <fstream>
using std::ifstream;

class Validator {
private:
	static const short CHECK_MULTY = 103;//prime
	static const uint32_t CHECK_MOD = 1'091'177;//its prime
	uint32_t checksum = 0;
public:
	Validator() = default;
	~Validator() = default;
	void addToSum(const uint32_t num);
	void resetSum();
	uint32_t getSum() const;
	/// @brief Reads from binary file compressed code, created a new checksum for it and compares with the original code checksum encoded in it.
	/// @warning Checksum value will be reset when this function is called! Input should start from the code part.
	bool isValid(ifstream& input, const uint32_t C_END);
};