#include "Compressor.h"



uint32_t Compressor::compress(istream& input, ostream& output)
{
	Validator validator;
	//we dont need counter for its size, we will use dict.size()
	unordered_map<string, uint32_t > dict;
	for (unsigned short i = 0; i < 256; i++) {//add char values as base
		dict[std::string(1, i)] = i;//add string made of 1 char(i)
	}                               //with value i

	//It's  just  a prefix that  we'll store things in and compare  things to nowand then
	string current_prefix;
	string current_string;//current   prefix  plus the next character in the  charstream
	char nextChar = 0;//one byte of file
	//
	//Loading screen helper- gets size
	input.seekg(0, std::ios::end);
	size_t progressDevider = input.tellg() / 10;
	size_t progrCounter = 0;
	input.seekg(0, std::ios::beg);
	std::cout << "[";
	bool isEmpty = input.peek() == std::ifstream::traits_type::eof();;
	//
	while (input.read(&nextChar, 1))
	{
		++progrCounter;
		if (progrCounter == progressDevider) {
			std::cout << "#";
			progrCounter = 0;
		}

		current_string = current_prefix + nextChar;
		if (dict.find(current_string) != dict.end()) {
			//we have that entry, continue
			current_prefix = current_string;
		}
		else {
			//we should add it in the table
			dict[current_string] = (uint32_t)dict.size();//we insert with value the next untaken number
			output.write((const char*)&dict[current_prefix], sizeof(uint32_t));//we know that it exists,output its code
			validator.addToSum(dict[current_prefix]); //making checksum that we will return later
			current_prefix = nextChar;
		}
	}
	//after we are done, we should output the code for the last prefix
	if (!isEmpty) {
		output.write((const char*)&dict[current_prefix], sizeof(uint32_t));
		validator.addToSum(dict[current_prefix]);
	}
	std::cout << "]\n";

	output.write((const char*)&C_END, sizeof(uint32_t)); //write code-end symbow
	return validator.getSum();
}

void Compressor::expand(istream& input, ostream& output)
{
	unordered_map<uint32_t, string> dict;
	for (unsigned short i = 0; i < 256; i++) {//add char values as base
		dict[i] = std::string(1, (char)i);//add number i as key
	}                               //with value string made of 1 char(i)

	uint32_t current_code = 0;
	uint32_t  old_code;
	string translated;

	input.read((char*)&old_code, sizeof(uint32_t));//get root, it should be in the table
	if (old_code == Compressor::C_END)//empty
	{
		return;
	}
	output << dict[old_code];//output the first character

	while (input.read((char*)&current_code, sizeof(uint32_t)) &&
		current_code != C_END) {//we take the code that have been in the table

		if (dict.find(current_code) != dict.end())
		{//exits in the table so we output it as string value
			translated = dict[current_code];
			output.write(translated.c_str(), translated.size());
			dict[dict.size()] = dict[old_code] + translated[0];//add entry for old as prefix and first char of the found str
			old_code = current_code;
		}
		else {//not in the table
			//We got code that is not in the table, however we can easily guess 
			//what the value will be by getting the prefix from the last iteration
			//and adding it's first letter to it's end
			translated = dict[old_code];
			translated += translated[0];//thats our new entry
			output.write(translated.c_str(), translated.size());
			dict[dict.size()] = translated;
			old_code = current_code;
		}
	}
	input.read((char*)&current_code, sizeof(uint32_t));//checksum value- we dont need it here
	//std::cout << "Dict size:" << dict.size();

}

