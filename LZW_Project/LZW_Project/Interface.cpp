#include "Interface.h"

//Archive bits structure:
// -some num of chars-   -exactly one char-  -some num of 32-bit uint- -one u_int32- -one u_int32-    | Repeat for other files
//     (Name)              (NAME_END_SYMB)           (Code)               (C_END)     (EC value)	  |     in the archive
//(Note: If the last name char is NAME_EMPT_DIR then empty dir will be created)

void Interface::executeCommand(std::string commandLine)
{
	processCommand(commandLine);

	switch (getCommand())
	{
	case CommandOption::_using:
	{
		setUsing();
		break;
	}
	case CommandOption::_zip:
	{
		zip();
		break;
	}
	case CommandOption::_unzip:
	{
		unzip();
		break;
	}
	case CommandOption::_info:
	{
		info();
		break;
	}
	case CommandOption::_refresh:
	{
		refresh();
		break;
	}
	case CommandOption::_ec:
	{
		errorCheck();
		break;
	}
	case CommandOption::_help:
	{
		help();
		break;
	}
	case CommandOption::_show:
	{
		show();
		break;
	}
	case CommandOption::_exit:
	{
		exit();
		break;
	}
	case CommandOption::_add:
	{
		add();
		break;
	}
	case CommandOption::_remove:
	{
		remove();
		break;
	}
	default:
		throw std::invalid_argument("Invalid command");
		break;
	}
}

void Interface::setUsing()
{
	usedArchive = getOneParamether();
	removeQuotes(usedArchive);
	if (!isArchiveFile(usedArchive)) {
		std::cerr << "Error: " << usedArchive << " is not an archive file. No changes were made.\n";
		usedArchive.clear();
	}
	else {
		std::cout << "Using " << usedArchive << std::endl;
	}
}

void Interface::zip()
{
	std::string archiveName = getOneParamether();
	removeQuotes(archiveName);

	if (archiveName.empty()) {
		if (!isPositiveAnswer("No file directory found. Do you want to create it as Code.lzw in program folder?")) {
			return;
		}
		archiveName = "Code";
	}
	archiveName += ".lzw";//add extenshion
	ofstream outputCode(archiveName, std::ios::binary);
	if (!outputCode) {
		std::cout << "Archive \"" << archiveName << "\" could not be opened for writting.\n";
		return;
	}
	//
	std::cout << "Files to be compressed:    (Type END to stop)\n";
	std::string name;
	vector<string> allNames;
	while (true)
	{
		std::cout << ">";
		std::getline(std::cin, name);
		if (name == "END" || name == "end") break;
		removeQuotes(name);
		std::string dir = getDirectory(name);
		allNames = std::move(getAllWithEqualName(dir, takeFileName(name)));//In case there is '?' or '*' that will get all files/folders with the name
		for (auto& addr : allNames) {
			if (fs::is_directory(addr)) {
				compressDirectory(addr, outputCode);
			}
			else {//its a single file
				compressFile(addr, outputCode);
			}
		}
	}
	outputCode.close();
	std::cout << "Files were archived successfully!\n";
}

void Interface::unzip()
{
	auto archiveName = getTwoParamether();
	removeQuotes(archiveName.first);
	removeQuotes(archiveName.second);
	if (archiveName.second.empty()) { //check if we have archive name
		if (usedArchive.empty()) {
			std::cerr << "Error: No archive is currently used or found as a command parameter.\n"; return;
		}
		archiveName.second = usedArchive;
	}
	else if (!fs::exists(archiveName.second) || !isArchiveFile(archiveName.second)) {
		std::cerr << "Error: " << archiveName.second << " does not exist or is not an archive file.\n"; return;
	}
	try {
		if (archiveName.first.empty()) {
			if (!isPositiveAnswer("No file directory found. Do you want to expand in a Results folder in the program directory?")) {
				return;
			}
			archiveName.first = "Results";
		}
		if (fs::exists(archiveName.first)) {
			if (!fs::is_directory(archiveName.first) &&
				isPositiveAnswer(archiveName.first + " exists but is not a directory.Do you want to try to create dir with such name?")) { //it's a file or something else
				fs::create_directories(archiveName.first);
			}
		}
		else if (isPositiveAnswer(archiveName.first + " not found. Do you want to create just directory?")) {
			fs::create_directories(archiveName.first);
		}
	}
	catch (...) {
		std::cerr << "Error: There was a problem with that directory. Operation could not complete.\n";
		return;
	}
	//now we have the directory
	ifstream input(archiveName.second, std::ios::binary);//our file with compressed code
	if (isPositiveAnswer("Do you want to expand all files or list specific names of files/directories?")) {
		expandHelper(input, archiveName.first, true); //expand all 
	}
	else {
		vector<std::string> names;
		getFilesToExpand(names);
		expandHelper(input, archiveName.first, false, names);
	}

}

void Interface::info()
{
	std::string archiveName = getOneParamether();
	removeQuotes(archiveName);
	if (archiveName.empty()) {
		if (usedArchive.empty()) {
			std::cerr << "Error : No archive name was found with the command.\n";
			return;
		}
		else {
			archiveName = usedArchive;
		}
	}
	if (!isArchiveFile(archiveName)) {
		std::cerr << "Error: " << archiveName << " is not an archive file.\n";
	}
	ifstream input(archiveName, std::ios::binary);
	if (!input) {
		std::cerr << "Error: Couldn't open " << archiveName << std::endl;
		return;
	}
	std::string name;
	char symb;
	unsigned long long size;
	uint32_t el;
	unsigned counter = 1;
	std::cout << "Archived files in " << archiveName << " :\n";
	while (!input.eof()) {
		size = 0;
		name.clear();
		while (input.read(&symb, 1) && symb != Compressor::NAME_END_SYMB)//we get the name
		{
			name += symb;
		}
		if (name.empty()) break; //sometimes .eof wont be set but there is nothing more to read
		if (name.back() != Compressor::NAME_EMPT_DIR) {
			while (input.read((char*)&el, sizeof(uint32_t)) && el != Compressor::C_END)
			{
				size += 4;
			}
			input.read((char*)&el, sizeof(uint32_t));//checksum
			std::cout << counter++ << ". " << name << std::endl;
			std::cout << "\tWith compressed size of " << size << " Bytes" << std::endl;
		}
		else {
			std::cout << counter++ << ". " << name << " (Empty Folder)" << std::endl;
		}
	}
}

void Interface::refresh()
{
	auto archiveName = getTwoParamether();//file to replace with and archive
	removeQuotes(archiveName.first);
	removeQuotes(archiveName.second);
	if (archiveName.second.empty()) { //check if we have archive name
		if (usedArchive.empty()) {
			std::cerr << "Error: No archive is currently used or found as a command parameter.\n"; return;
		}
		archiveName.second = usedArchive;
	}
	else if (!isArchiveFile(archiveName.second) || !fs::exists(archiveName.second)) {
		std::cerr << "Error: " << archiveName.second << " does not exist or is not an archive file.\n";
		return;
	}
	if (!fs::exists(archiveName.first)) {
		std::cerr << "Error: " << archiveName.first << " could not be found.\n";
		return;
	}
	if (fs::is_directory(archiveName.first)) {
		std::cerr << "Error: Folder refresh not supported.\n";
		return;
	}
	std::string newFileName = std::move(takeFileName(archiveName.first)); //the file name that we want to replace
	vector<std::string> sameNames; //vector that will store every file with same filename as the searched one
	//
	ifstream input(archiveName.second, std::ios::binary);
	if (!input) {
		std::cout << "Error: There was a problem with opening " << archiveName.first << ".No changes were made." << std::endl;
		return;
	}
	std::string name;//temporary
	uint32_t code;
	char symb;
	while (!input.eof()) {//we get all the names
		name.clear();
		while (input.read(&symb, 1) && symb != Compressor::NAME_END_SYMB)//we get the name
		{
			name += symb;
		}
		if (name.empty()) break; //sometimes .eof wont be set but there is nothing more to read
		if (takeFileName(name) == newFileName) {
			sameNames.push_back(name);
		}
		if (name.back() != Compressor::NAME_EMPT_DIR) {
			while (input.read((char*)&code, sizeof(uint32_t)) && code != Compressor::C_END) {}//skip the code, we dont need it
			input.read((char*)&code, sizeof(uint32_t)); //skip checksum as well
		}
	}
	if (sameNames.empty())
	{
		std::cout << "No files were found with name " << newFileName << " in " << archiveName.second << std::endl;
		input.close();
		return;
	}
	int choice = 1;
	if (sameNames.size() > 1) {
		std::cout << "There are multiple files with that name. Which one do you want to replace? (Input a number)\n";
		do {
			for (int i = 1; i <= sameNames.size(); i++) {
				std::cout << i << "." << sameNames[i - 1] << std::endl;
			}
			std::cout << ">";
			std::cin >> choice;
		} while (choice <= 0 || choice > sameNames.size());
	}
	std::cout << "Replacing " << sameNames[choice - 1] << std::endl;
	input.clear();//clear flags
	input.seekg(0);//reset reading pointer
	try {
		replaceFile(sameNames[choice - 1], input, archiveName.second, true, archiveName.first);
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		input.close();
		return;
	}
	std::cout << "Replaced successfully.\n";

}

void Interface::replaceFile(const std::string& toReplace, ifstream& archiveFile, const std::string& archiveName, bool isReplacing , const std::string& newFileDir )
{
	const std::string tempName = getDirectory(archiveName) + "\\Refresh_TempFile_DoNotDelete.temp";
	ofstream temp(tempName, std::ios::binary);
	if (!temp) {
		throw std::runtime_error("Error: Couldn't open file " + tempName);
	}
	ifstream replacer;
	if (isReplacing) {
		replacer.open(newFileDir, std::ios::binary);
		if (!replacer) {
			throw std::runtime_error("Error: Couldn't create temporary file for the operation.");
		}
	}
	std::string name;
	uint32_t code;
	char symb;
	while (!archiveFile.eof()) {
		name.clear();
		while (archiveFile.read(&symb, 1) && symb != Compressor::NAME_END_SYMB)//we get the name
		{
			name += symb;
		}
		if (name.empty()) break; //sometimes .eof wont be set but there is nothing more to read
		if (isReplacing || name != toReplace) {//we wont copy the name if we want to erase it 
			temp.write(name.c_str(), name.size());//write the name in both cases
			temp.write(&symb, 1);//name end
		}
		if (name == toReplace) {//replace the file or skip if deleting
			if (isReplacing) {
				code = Compressor::compress(replacer, temp);//checksum
				temp.write((const char*)&code, sizeof(uint32_t));
			}
			//now skip the rest of the old file
			while (archiveFile.read((char*)&code, sizeof(uint32_t)) && code != Compressor::C_END) {}
			archiveFile.read((char*)&code, sizeof(uint32_t)); //skip checksum as well
		}
		else if (name.back() != Compressor::NAME_EMPT_DIR) {//just copy it if not empty dir
			while (archiveFile.read((char*)&code, sizeof(uint32_t)) && code != Compressor::C_END) {
				temp.write((const char*)&code, sizeof(uint32_t));
			}
			temp.write((const char*)&Compressor::C_END, sizeof(uint32_t));//code end
			archiveFile.read((char*)&code, sizeof(uint32_t)); //checksum
			temp.write((const char*)&code, sizeof(uint32_t));
		}
	}
	//now we need to delete old file and rename the new one
	archiveFile.close();
	temp.close();
	fs::remove(archiveName);
	try {
		fs::rename(tempName, archiveName);
	}
	catch (const fs::filesystem_error&) {
		std::cerr << "Fatal Error: File " << archiveName << " was copied to " << tempName << " but could not be renamed.\n";
	}
}

void Interface::errorCheck()
{
	Validator validator;
	std::string archiveName = getOneParamether();
	removeQuotes(archiveName);
	if (archiveName.empty()) {
		if (usedArchive.empty()) {
			std::cerr << "Error : No archive name was found with the command.\n";
			return;
		}
		else {
			archiveName = usedArchive;
		}
	}
	if (!isArchiveFile(archiveName)) {
		std::cerr << "Error: " << archiveName << " is not an archive file.\n";
	}
	ifstream input(archiveName, std::ios::binary);
	if (!input) {
		std::cerr << "Error: Couldn't open " << archiveName << std::endl;
		return;
	}
	std::string name;
	char symb;
	while (!input.eof()) {
		name.clear();
		while (input.read(&symb, 1) && symb != Compressor::NAME_END_SYMB)//we get the name
		{
			name += symb;
		}
		if (name.empty()) break; //sometimes .eof wont be set but there is nothing more to read
		if (!validator.isValid(input, Compressor::C_END))
		{
			std::cout << "There was found a problem with " << name << ":\n\t-It is possible that the file is changed or damaged!\n";
		}
		else {
			std::cout << name << " is good.\n";
		}
	}
}

void Interface::help()
{
	std::cout << "--------------------Help section----------------------\n";
	std::cout << "Valid commands :\n";
	std::cout << "(Commands are not case-sensitive and there can be more than one whitespace between parameters)\n";
	std::cout << "(Any full directory adresses can be used both with or without quoting)\n";
	std::cout << ">Using archive_name \n";
	std::cout << "~(^Sets the archive as currently used.That will make it easier for unzip, refresh, EC, info commands to be used without telling files name each time)\n";
	std::cout << ">ZIP new_archive_name\n";
	std::cout << "~(^Starts making new archive with the given name or directory.Extenshion lzw will be added to the name. Then you can add files or directories to be compressed in it)\n";
	std::cout << ">UNZIP path_to_folder (optional)archive_name \n";
	std::cout << "~(^Starts unzipping process.If no archive name is presented, Using one is set.Then you can choose which file to be expanded to path_to_folder)\n";
	std::cout << ">Info (optional)archive_name \n";
	std::cout << "~(^Shows the files that are zipped in it)\n";
	std::cout << ">Refresh file_name (optional)archive_name \n";
	std::cout << "~(^If file_name exists zipped in the file ,it will be replaced with the new version.It multiple exist, user will be asked to choose)\n";
	std::cout << ">EC (optional)archive_name\n";
	std::cout << "~(^Checks if files have been modified outside the program and annouces if such are presented)\n";
	std::cout << ">Add file_name (optional)archive_name\n";
	std::cout << "~(^Adds the file to the archive)\n";
	std::cout << ">Remove file_name (optional)archive_name\n";
	std::cout << "~(^Removes the file with that exact name from the archive)\n";
	std::cout << ">HELP\n";
	std::cout << "~(^Prints the commands again)\n";
	std::cout << ">Show\n";
	std::cout << "~(^Shows the file that is set by Using command)\n";
	std::cout << ">EXIT\n";
	std::cout << "~(^Exits from program)\n\n";
	std::cout << "-------------------------------------------------------\n";
}

void Interface::show()
{
	std::cout << (usedArchive.empty() ? "No archive name is currently used." :
		"Currently using : " + usedArchive) << std::endl;
}

void Interface::exit()
{
	throw ExitProgram();
}

void Interface::remove()
{
	auto archiveName = getTwoParamether();//file to replace with and archive
	removeQuotes(archiveName.first);
	removeQuotes(archiveName.second);
	if (archiveName.second.empty()) { //check if we have archive name
		if (usedArchive.empty()) {
			std::cerr << "Error: No archive is currently used or found as a command parameter.\n"; return;
		}
		archiveName.second = usedArchive;
	}
	else if (!isArchiveFile(archiveName.second) || !fs::exists(archiveName.second)) {
		std::cerr << "Error: " << archiveName.second << " does not exist or is not an archive file.\n";
		return;
	}
	ifstream input(archiveName.second, std::ios::binary);
	if (!input) {
		std::cout << "Error: There was a problem with opening " << archiveName.first << ".No changes were made." << std::endl;
		return;
	}
	std::cout << "Removing " << archiveName.first << " ..." << std::endl;
	try {
		replaceFile(archiveName.first, input, archiveName.second, false);
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		input.close();
		return;
	}
	std::cout << archiveName.first << " was removed.\n";
}

void Interface::add()
{
	auto archiveName = getTwoParamether();//file to replace with and archive
	removeQuotes(archiveName.first);
	removeQuotes(archiveName.second);
	if (archiveName.second.empty()) { //check if we have archive name
		if (usedArchive.empty()) {
			std::cerr << "Error: No archive is currently used or found as a command parameter.\n";
			return;
		}
		archiveName.second = usedArchive;
	}
	else if (!isArchiveFile(archiveName.second) || !fs::exists(archiveName.second)) {
		std::cerr << "Error: " << archiveName.second << " does not exist or is not an archive file.\n";
		return;
	}
	ofstream outputCode(archiveName.second, std::ios::binary | std::ios::app);
	if (!outputCode) {
		std::cout << "Archive \"" << archiveName.second << "\" could not be opened for writting.\n";
		return;
	}
	//
	if (fs::is_directory(archiveName.first)) {
		compressDirectory(archiveName.first, outputCode);
	}
	else {//its a single file
		compressFile(archiveName.first, outputCode);
	}
	outputCode.close();
	std::cout << "Files were archived successfully!\n";
}

bool Interface::isPositiveAnswer(const string& question)
{
	std::cout << question << std::endl;
	std::cout << "[Y/N] >";
	std::string ans;
	std::getline(std::cin, ans);
	return ans == "Y" || ans == "y";
}

void Interface::removeQuotes(std::string& str)
{
	if (str.size() >= 2 && str.front() == '\"' && str.back() == '\"')
	{
		str = str.substr(1, str.size() - 2);
	}
}

void Interface::expandHelper(ifstream& input, std::string& folderName, bool expandAll, const vector<std::string>& names)
{
	folderName += '\\';
	std::string name;
	char symb = 0;
	while (!input.eof()) {
		name.clear();
		while (input.read(&symb, 1) && symb != Compressor::NAME_END_SYMB)//we get the name
		{
			name += symb;
		}
		if (name.empty()) break; //sometimes .eof wont be set but there is nothing more to read

		if (expandAll || existsInVector(name, names))//its a file that we are looking for
		{
			name = folderName + name;//we are making the full adress of our item
			if (name.back() == Compressor::NAME_EMPT_DIR) {//its an empty folder
				//name.pop_back();
				fs::create_directories(name);
				std::cout << "Made (empty) folder " << name << std::endl;
				continue;
			}
			std::string folders = getDirectory(name);//contains the full adress with folders without the file
			fs::create_directories(folders); //if there are missing folders- create them before making file
			std::cout << "Expanding in " << name << std::endl;
			ofstream output(name, std::ios::binary);
			if (!output) {
				std::cout << "Error: Couldnt open " << name << std::endl;
				uint32_t c;//lets skip that file with wrong name...
				while (input.read((char*)&c, sizeof(uint32_t)) && c != Compressor::C_END) {}//skip code
				input.read((char*)&c, sizeof(uint32_t));//skip checksum
			}
			else {
				Compressor::expand(input, output);
			}
		}
		else {//we dont need it - skip
			if (name.back() == Compressor::NAME_EMPT_DIR) continue;
			uint32_t c;
			while (input.read((char*)&c, sizeof(uint32_t)) && c != Compressor::C_END) {}//skip code
			input.read((char*)&c, sizeof(uint32_t));//skip checksum
		}
	}
	std::cout << "Files were expanded successfully!\n";
}

void Interface::getFilesToExpand(vector<std::string>& names)
{
	std::cout << "\nFiles/directories to be expanded:  (type END when ready)\n";
	std::string input;
	while (true) {
		std::cout << ">";
		std::getline(std::cin, input);
		if (input == "END" || input == "end") break;
		removeQuotes(input);
		names.push_back(input);
	}
}

bool Interface::isArchiveFile(const std::string& name)
{
	return name.size() >= 4 && name.substr(name.size() - 4) == ".lzw";
}

bool Interface::existsInVector(const std::string& el, const vector<std::string>& arr) const
{
	for (size_t i = 0; i < arr.size(); i++) {
		if (areEqual(el.c_str(), arr[i].c_str())) return true;
	}
	return false;
}

std::string Interface::takeFileName(const std::string& fullAddress) const
{
	if (fullAddress.empty()) return std::string();

	for (size_t i = fullAddress.size() - 1; i > 0; i--) {//search for '\'
		if (fullAddress[i] == '\\') return fullAddress.substr(i + 1);
	}
	return std::string(fullAddress);
}

void Interface::compressFile(const std::string& name, ofstream& outputCode, const std::string& folder)
{
	ifstream input(name, std::ios::binary);
	if (!input || !outputCode)//|| !output 
	{
		std::cout << "Couldn't open the file " << name << std::endl;
		return;
	}
	std::cout << "Compressing " << name << "..." << std::endl;
	if (folder.empty()) {
		std::string newName = takeFileName(name);
		outputCode.write(newName.c_str(), newName.size());//write the name of the file , folder = folders+current_name
	}
	else {
		outputCode.write(folder.c_str(), folder.size());//write the name of the file
	}
	outputCode.write(&Compressor::NAME_END_SYMB, 1);//write symbow for end of file name
	uint32_t checksum = Compressor::compress(input, outputCode); //write the code and get the checksum
	outputCode.write((const char*)&checksum, sizeof(checksum)); //and write the checksum for error-checking
	input.close();
}

void Interface::compressDirectory(const std::string& name, ofstream& outputCode, const std::string& folder)
{
	try {
		if (!folder.empty()) std::cout << "Looking at " << folder << std::endl; //output the folder we are in
		bool isEmpty = true;
		for (const auto& entry : fs::directory_iterator(name)) {//get files/directories in the name directory
			isEmpty = false;
			if (entry.is_directory()) {
				compressDirectory(entry.path().string(), outputCode, folder + takeFileName(entry.path().string()) + '\\');
			}
			else {
				compressFile(entry.path().string(), outputCode, folder + takeFileName(entry.path().string()));
			}
		}
		if (isEmpty) {//directory is empty but we should still save it in the archive
			if (folder.empty()) {
				std::string newName = takeFileName(name);
				outputCode.write(newName.c_str(), newName.size());//write the name of the folder which contains also the name of dir
			}
			else {
				outputCode.write(folder.c_str(), folder.size());//write the name of the dir
			}
			outputCode.write(&Compressor::NAME_EMPT_DIR, 1);//also add the symbow for empty directory
			outputCode.write(&Compressor::NAME_END_SYMB, 1);//write symbow for end of file name
		}
	}
	catch (...) { //(const fs::filesystem_error&) {
		std::cout << "There was a problem with directory " << name << ".Make sure it exists and can be accessed.\n";
	}

}

std::string Interface::getDirectory(const std::string& adress)
{
	if (!adress.empty()) {
		for (size_t i = adress.size() - 1; i > 0; i--) {
			if (adress[i] == '\\') {
				return adress.substr(0, i);
			}
		}
	}
	return string();
}

inline bool Interface::isNotSpecial(const char chr) const
{
	return chr != '*' && chr != '?';
}

bool Interface::areEqual(const char* first, const char* second) const
{
	if (!*first && !*second) return true;//both have got to an end
	if (isNotSpecial(*first) && isNotSpecial(*second) && *first != *second) return false;//will also validate the case where one is ended but other not
	if (*second == '*') {
		std::swap(first, second); //and go to the next if
	}
	if (*first == '*') {
		while (*first && *first == '*') {//find the first non-star character
			++first;
		}
		if (!*first) return true; //his last symbow was * so it's a match
		for (unsigned i = 0; second[i] != '\0'; i++) {
			if (second[i] == *first || second[i] == '*' || *first == '?') {//we found a match
				if (areEqual(second + i, first)) {
					return true;
				}
			}
		}
		return false;
	}
	if (*first == '?' || *second == '?') return areEqual(first + 1, second + 1); //'?' replaces anything and we have checked for * already
	return areEqual(first + 1, second + 1);
}

vector<string> Interface::getAllWithEqualName(std::string& folder, const std::string& name)
{
	vector<string> allNames;
	string fileName;
	if (folder.empty())//we are in the directory of the program
	{
		folder = getDirectory(fs::absolute("main.cpp").string());
	}
	try {
		for (auto& entry : fs::directory_iterator(folder)) {//will it throw?
			fileName = takeFileName(entry.path().string());
			if (areEqual(fileName.c_str(), name.c_str())) //<-thats ugly...
			{
				allNames.push_back(entry.path().string());
			}
		}
	}
	catch (const fs::filesystem_error&) {
		std::cout << "No files or directories found in " << folder << " with name " << name << std::endl;
	}
	return allNames;
}
