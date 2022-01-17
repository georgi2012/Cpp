#include "interface.h"
#include <fstream>


using std::fstream;

const string name1 = "LongTest1.txt";
const string name2 = "LongTest2.txt";

void createFile1() { //~300MB
	fstream file(name1, std::ofstream::out | std::ofstream::trunc);
	if (!file) {
		std::cout << "Cant open file " << name1 << std::endl;
		throw - 1;
	}
	for (int i = 0; i < 1000000; i++) {
		file << "one ";
		if (i % 300 == 0) file.flush();
	}
	file.flush();
	for (int i = 0; i < 200000; i++) {
		file << "two ";
		if (i % 300 == 0) file.flush();
	}
	file.flush();
	unsigned ohNo = -1;
	ohNo /= 400;
	for (int i = 0; i < 300000; i++) {
		file << "uwu ";
		if (i % 300 == 0) file.flush();
	}
	file.flush();
	for (int i = 0; i < ohNo; i++) {
		file << "SomeSUperDuperLongWordLikeThis ";
		if (i % 300 == 0) file.flush();
	}
	file.flush();
	file.close();
}

void createFile2() {
	fstream file(name2, std::ofstream::out | std::ofstream::trunc);
	if (!file) {
		std::cout << "Cant open file " << name2 << std::endl;
		throw - 1;
	}
	int i = 0;
	for (i = 0; i < 100001; i++) {
		file << "one ";
		if (i % 300 == 0) file.flush();
	}
	//std::cout <<"I="<< i;
	file.flush();
	for (i = 0; i < 20001; i++) {
		file << "two ";
		if (i % 300 == 0) file.flush();
	}
	//std::cout << "I=" << i;
	file.flush();
	for (i = 0; i < 30001; i++) {
		file << "uwu ";
		if (i % 300 == 0) file.flush();
	}
	//std::cout << "I=" << i;
	file.flush();
	file.close();

}


int main(int argc, char* argv[]) {

	std::cout << "Making big file1...\n";
	createFile1();
	fstream file1;
	file1.open(name1);
	std::cout << "Making big file2...\n";
	createFile2();
	fstream file2;
	file2.open(name2);
	std::cout << "Processing...\n";
	Comparator c;
	ComparisonReport report = c.compare(file1, file2);
	std::cout << "Completed!\n";
	std::cout << "Data:\n";
	std::cout << "\tUnique in file1:" << report.uniqueWords[0].countOfUniqueWords() << std::endl;
	std::cout << "\t\tone in file1:" << report.uniqueWords[0].countOf("one") << std::endl;
	std::cout << "\t\tuwu in file1:" << report.uniqueWords[0].countOf("uwu") << std::endl;
	std::cout << "\t\ttwo in file1:" << report.uniqueWords[0].countOf("two") << std::endl;
	std::cout << "\t\tSomeSUperDuperLongWordLikeThis in file1:" << report.uniqueWords[0].countOf("SomeSUperDuperLongWordLikeThis") << std::endl;
	std::cout << "\tData:\n";
	std::cout << "\tUnique in file2:" << report.uniqueWords[1].countOfUniqueWords() << std::endl;
	std::cout << "\t\tone in file2:" << report.uniqueWords[1].countOf("one") << std::endl;
	std::cout << "\t\tuwu in file2:" << report.uniqueWords[1].countOf("uwu") << std::endl;
	std::cout << "\t\ttwo in file2:" << report.uniqueWords[1].countOf("two") << std::endl;
	std::cout << "\t\tSomeSUperDuperLongWordLikeThis in file2:" << report.uniqueWords[1].countOf("SomeSUperDuperLongWordLikeThis") << std::endl;
	std::cout << "\tData:\n";
	std::cout << "\tCommon:" << report.commonWords.countOfUniqueWords() << std::endl;
	std::cout << "\t\tone:" << report.commonWords.countOf("one") << std::endl;
	std::cout << "\t\tuwu:" << report.commonWords.countOf("uwu") << std::endl;
	std::cout << "\t\ttwo:" << report.commonWords.countOf("two") << std::endl;
	std::cout << "\t\tSomeSUperDuperLongWordLikeThis:" << report.commonWords.countOf("SomeSUperDuperLongWordLikeThis") << std::endl;
}



