#pragma once
#include <filesystem>
#include <vector>
#include "Compressor.h"
#include "Commands.h"
#include "Exception_ExitProgram.h"
#include "Validator.h"


using std::vector;
namespace fs = std::filesystem;

/// @brief Responsible for working with command line . Uses command to recognize command and extract parameters ,then calls the right functions . Inherits Commands
///  Most methods extract the parameters needed using methods that come from Commands class. Files created by the archiver have .lzw extenshion.
class Interface : protected Commands {
private:
	/// @brief The name of the archive set with Using command.
	std::string usedArchive;
	/// @brief Sets the string name of directory as currently used.
	void setUsing();
	/// @brief Takes new zip name and then asks for files to be zipped in it as compressing happens after each file name listed.
	void zip();
	/// @brief Takes directory for expanding data and the arhive name to be expanded.User will be asked if he wants to expand all data or list specific names from the archive.
	void unzip();
	/// @brief Goes through the file, extrancting archived data names and their size. It shows the data in the standart input.
	void info();
	/// @brief Takes file name and archive. Finds all files with that name and asks the user which one he wants to replace in the archive.(Temp archive will be created in the process of replacing.It will be delated later)
	void refresh();
	/// @brief (Used by EC command) Checks if the checksum code in the archive for every file is valid. If not - user will be warned that the file might be changed or damaged.
	void errorCheck();
	/// @brief Prints on console the commands and rules how to be used properly.
	void help();
	/// @brief Shows the archive that is set as used at the momment.
	void show();
	/// @brief Throws ExitProgram exception to warn that Exit command is being executed.
	/// @warning ExitProgram exception should be caught wherever the class is used!
	void exit();
	/// @brief Removes files from archive with given name if found in the file. 
	void remove();
	/// @brief Adds a new file to the archive (added to it's end).
	void add();
	/// @brief Used to ask user a question that can be answered with Yes or No and returns if answer is yes.
	bool isPositiveAnswer(const string& question);
	/// @brief Removes quotes around string if there are any.
	void removeQuotes(std::string& str);
	/// @brief Makes sure that just files from names vector will be expanded (or all if expandAll bool is set)
	void expandHelper(ifstream& input, std::string& folderName, bool expandAll = false,const vector<std::string>& names=vector<std::string>());
	/// @brief Gets the input of all names that will later be looked for in the archived file.
	/// @param names String vector of names 
	void getFilesToExpand(vector<std::string>& names);
	/// @brief Returns if the file have .lzw extenshion.
	bool isArchiveFile(const std::string& name);
	/// @brief Checks if element exists in the vector.
	bool existsInVector(const std::string& el, const vector<std::string>& arr) const;
	/// @brief Takes just the name of the file from the full address
	std::string takeFileName(const std::string& fullAddress) const;
	/// @brief Compress a single file.
	/// @param folder added to the name of file when added in archive.That way we know if we should create folder with expand. Used when called from comressDirectory
	void compressFile(const std::string& name, ofstream& outputCode,const std::string& folder=std::string());
	/// @brief Compress all files in a directory and recursively call the function for any folders in the directory.
	void compressDirectory(const std::string& name, ofstream& outputCode, const std::string& folder = std::string());
	/// @brief Receives full adress and returns the folders before the final file.
	std::string getDirectory(const std::string& adress);
	/// @brief Checks if the character is not '?' or '*' ,helper for areEqual
	bool isNotSpecial(const char chr) const;
	/// @brief Returns if two character strings are equal and works with '*' and '?'
	/// as '*' can replace one or more characters and '?' can replace one character
	bool areEqual(const char* first, const char* second) const;
	/// @brief Iterates over folder directory and gets all files with name equal to @name using areEqual function.
	vector<string> getAllWithEqualName( std::string& folder, const std::string& name);
	/// @brief Replaces file @toReplace with the compressed info of @newFileDir in @archiveName stream. If isReplacin is false, file will be deleted
	void replaceFile(const std::string& toReplace,ifstream& archiveFile, const std::string& archiveName,bool isReplacing=true, const std::string& newFileDir = "");
public:
	Interface() = default;
	~Interface() noexcept = default;
	/// @brief Uses Command::processCommand() and switches the command . Calls the proper functon for it's execution.
	/// @param commandLine String containing both command and parameters.
	/// @warning Invalid commands will throw std::invalid_argument .
	void executeCommand(std::string commandLine);


};