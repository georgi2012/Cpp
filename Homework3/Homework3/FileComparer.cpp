#include "FileComparer.h"

void FileComparer::validateFiles(const std::string& fileName1, const std::string& fileName2)
{
	std::ifstream file(fileName1);
	if (!file) {
		throw std::runtime_error("File " + fileName1 + " does not exist or can not be opened.");
	}
	file.close();
	file.open(fileName2);
	if (!file) {
		throw std::runtime_error("File " + fileName2 + " does not exist or can not be opened.");
	}
	file.close();
}

void FileComparer::additionalStat(ComparisonReport& cr)
{
	char choice = 0;
	std::cout << "\n---------------Additional Statistics-----------\n";
	do {
		std::cout << "\nIf you'd like to see more detailed stat you can:\n";
		std::cout << "Input 0: Exit \n";
		std::cout << "Input 1: Show unique words for first file.\n";
		std::cout << "Input 2: Show unique words for second file.\n";
		std::cout << "Input 3: Show common words for both files.\n";
		std::cout << ">";
		std::cin >> choice;
		switch (choice)
		{
		case '0': break;
		case '1': 
			showFile1Unique(cr);
			break;
		case '2':
			showFile2Unique(cr);
			break;
		case '3':
			showCommon(cr);
			break;
		default:
			std::cout << choice << " could not be recognized as a command.\n";
			break;
		}
	} while (choice != '0');

	std::cout << "\nExiting...\n";

}

void FileComparer::showFile1Unique(ComparisonReport& cr)
{
	std::cout << "Uniqie words for File 1:\n";
	for (auto el : cr.uniqueWords[0].umap) {
		std::cout << "\t" << el->key << " : " << el->value << std::endl;
	}
}

void FileComparer::showFile2Unique(ComparisonReport& cr)
{
	std::cout << "Uniqie words for File 2:\n";
	for (auto el : cr.uniqueWords[1].umap) {
		std::cout << "\t" << el->key << " : " << el->value << std::endl;
	}
}

void FileComparer::showCommon(ComparisonReport& cr)
{
	std::cout << "Common words for both files:\n";
	for (auto el : cr.commonWords.umap) {
		std::cout << "\t" << el->key<< " : " << el->value << std::endl;
	}
}

void FileComparer::removeQuotes(std::string& fileName1, std::string& fileName2)
{
	if (fileName1.size() >= 2 && fileName1.front() == '\"' && fileName1.back() == '\"')
	{
		fileName1 = fileName1.substr(1, fileName1.size() - 2);
	}
	if (fileName2.size() >= 2 && fileName2.front() == '\"' && fileName2.back() == '\"')
	{
		fileName2 = fileName2.substr(1, fileName2.size() - 2);
	}
}

void FileComparer::analizeFileDataFor(const std::string& fileName1,const std::string& fileName2)
{
	std::string fileC1 = fileName1;//for quotes removing
	std::string fileC2 = fileName2;
	removeQuotes(fileC1, fileC2);
	validateFiles(fileC1, fileC2);
	std::ifstream file1(fileC1);
	std::ifstream file2(fileC2);
	ComparisonReport cr = comparator.compare(file1, file2);
	file1.close();
	file2.close();
	fileC1.clear();
	fileC2.clear();
	std::cout << "---------------------Result---------------------\n";
	std::cout << "First file contains " << comparator.getFile1AllWordsCnt() << " words and " << comparator.getCommonForFiles() << " of them are also in the second file ";
	std::cout << "(" << (comparator.getFile1AllWordsCnt()==0? 100: comparator.getCommonForFiles()*100 / comparator.getFile1AllWordsCnt()) << "%).\n";
	std::cout << "Second file contains " << comparator.getFile2AllWordsCnt() << " words and " << comparator.getCommonForFiles() << " of them are also in the first file ";
	std::cout << "(" << (comparator.getFile2AllWordsCnt() == 0 ? 100 : comparator.getCommonForFiles()*100 / comparator.getFile2AllWordsCnt()) << "%).\n";
	additionalStat(cr);
}
