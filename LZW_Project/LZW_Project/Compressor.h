#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdint>//fixed int size
#include "Validator.h"

using std::ifstream; using std::istream;
using std::ofstream; using std::ostream;
using std::fstream;
using std::unordered_map;
using std::string;

class Compressor {
private:

public:
	static const char NAME_END_SYMB = 2;//STX char (start of text character)
	static const char NAME_EMPT_DIR = 0;//NULL char (tells that the name is an empty directory)
	static const uint32_t C_END = -2;//compress end 
	//Compressor()=default;
	//~Compressor() = default;
	static uint32_t compress(istream& input, ostream& output);
	static void expand(istream& input, ostream& output);
};
