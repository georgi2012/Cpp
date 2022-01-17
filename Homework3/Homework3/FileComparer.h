#pragma once
#include "interface.h"
#include <fstream>

class FileComparer {
private:
	Comparator comparator;

	/// @brief If strings have quotes around them, they'll be removed.
	void removeQuotes(std::string& fileName1, std::string& fileName2);
	/// @brief Checks if file with such names can be opened
	void validateFiles(const std::string& fileName1, const std::string& fileName2);
	/// @brief Shows additional info 
	void additionalStat(ComparisonReport& cr);
	void showFile1Unique(ComparisonReport& cr);
	void showFile2Unique(ComparisonReport& cr);
	void showCommon(ComparisonReport& cr);
public:
	FileComparer() = default;
	~FileComparer() = default;
	/// @brief Works with comparator to get the ComparisonReport and display information that is needed. 
	void analizeFileDataFor(const std::string& fileName1, const std::string& fileName2);

};