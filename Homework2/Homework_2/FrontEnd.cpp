#include "FrontEnd.h"
#include "BinaryTree.h"

FrontEnd::FrontEnd(const FrontEnd& other)
	:hierarchies(other.hierarchies)
{
}

FrontEnd::FrontEnd(const FrontEnd&& other) noexcept
{
	hierarchies = std::move(other.hierarchies);
}

FrontEnd::~FrontEnd() noexcept
{
	deleteHierarchies();
}

FrontEnd& FrontEnd::operator=(const FrontEnd& other)
{
	if (&other != this) {
		hierarchies.clearData();
		hierarchies = other.hierarchies;
	}
	return *this;
}

FrontEnd& FrontEnd::operator=(FrontEnd&& other) noexcept
{
	if (&other != this) {
		hierarchies = std::move(other.hierarchies);
	}
	return *this;
}

void FrontEnd::executeCommand(std::string commandLine)
{
	processCommand(commandLine);

	switch (getCommand())
	{
	case CommandOption::_invalid:
		throw std::invalid_argument("Command not valid");
		break;
	case CommandOption::_load:
		load();
		break;
	case CommandOption::_save:
		save();
		break;
	case CommandOption::_find:
		find();
		break;
	case CommandOption::_num_subordinates:
		num_subordinates();
		break;
	case CommandOption::_manager:
		manager();
		break;
	case CommandOption::_num_employees:
		num_employees();
		break;
	case CommandOption::_overloaded:
		num_overloaded();
		break;
	case CommandOption::_join:
		join();
		break;
	case CommandOption::_help:
		help();
		break;
	case CommandOption::_fire:
		fire();
		break;
	case CommandOption::_hire:
		hire();
		break;
	case CommandOption::_salary:
		salary();
		break;
	case CommandOption::_incorporate:
		incorporate();
		break;
	case CommandOption::_modernize:
		modernize();
		break;
	case CommandOption::_exit:
		exit();
		break;
	default:
		throw std::invalid_argument("Command not recognized");
		break;
	}
}

void FrontEnd::help()
{
	std::cout << "--------------------Help section----------------------\n";
	std::cout << "Valid commands :\n";
	std::cout << "(Commands are not case-sensitive and there can be more than one whitespace between parameters)\n";
	std::cout << ">load object_name file_name\n";
	std::cout << "~(^Loads the file and creates object of it)\n";
	std::cout << ">overloaded name_of_object \n";
	std::cout << "~(^Returns the number of overloaded employees)\n";
	std::cout << ">save object_name file_name\n";
	std::cout << "~(^Saves the object data in the file)\n";
	std::cout << ">find object_name employee_name\n";
	std::cout << "~(^Checks if the employee is in the object hierarchy)\n";
	std::cout << ">num_subordinates object_name employee_name \n";
	std::cout << "~(^Returns the number of direct subordinates)\n";
	std::cout << ">manager object_name employee_name\n";
	std::cout << "~(^Returns the name of the manager of the employee)\n";
	std::cout << ">num_employees object_name\n";
	std::cout << "~(^Returns the total number of employees in the object)\n";
	std::cout << ">join first_object second_object new_obj_name \n";
	std::cout << "~(^Creates a new object that is a combination of two others)\n";
	std::cout << ">fire object_name employee_name \n";
	std::cout << "~(^Removes the employee and rearrange his subordinates)\n";
	std::cout << ">hire object_name employee_name new_manager_name \n";
	std::cout << "~(^Hires or moves the employee and his subordinates to his new manager)\n";
	std::cout << ">salary object_name employee_name \n";
	std::cout << "~(^Returns the salary of the employee)\n";
	std::cout << ">incorporate object_name\n";
	std::cout << "~(^Incorporates the object)\n";
	std::cout << ">modernize object_name \n";
	std::cout << "~(^Modernizes the objects)\n";
	std::cout << ">EXIT\n";
	std::cout << "~(^Exits from program)\n\n";
	std::cout << "---------------------------------------------------\n";
}

void FrontEnd::exit()
{
	deleteHierarchies();
	throw ExitProgram();
}

void FrontEnd::deleteHierarchies()
{
	hierarchies.clearData();
}

Hierarchy* FrontEnd::findHierarchy(const std::string& name) const
{
	Hierarchy temp("", name);
	Hierarchy* found = &hierarchies.find(temp);
	return found;
}

string FrontEnd::readFromFile(const std::string& fileName) const
{
	std::ifstream file(fileName);
	if (file) {
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		string text(size, ' ');
		file.seekg(0);
		file.read(&text[0], size);
		file.close();
		return text;
	}
	else {
		throw FileCantLoad();
	}

}

void FrontEnd::writeInFile(const std::string& fileName, std::string& data) const
{
	std::fstream file(fileName);
	if (file.good()) {//already exists
		file.close();
		if (!agreesToDelete())
		{
			std::cout << "File was not rewritten. Data:\n" << data << std::endl;
			return;
		}
	}
	file.open(fileName, std::ofstream::out | std::ofstream::trunc); //delete content or create file
	if (file) {
		file << data;
		file.close();
		std::cout << "Data was saved in " << fileName << std::endl;
	}
	else {
		throw FileCantLoad();
	}
}

string FrontEnd::readFromConsole() const
{
	string allinput, inputline;
	while (std::getline(std::cin, inputline) && inputline != "^Z" && inputline != "^D")
	{
		allinput += inputline + '\n';
	}
	return allinput;
}

bool FrontEnd::agreesToDelete() const
{
	std::cout << "File with the given name already exists. Do you want to rewrite it and lose its current information ?\n";
	std::cout << "[Y/N]:";
	char ans;
	std::cin >> ans;
	return ans == 'Y' || ans == 'y';
}

void FrontEnd::load()
{
	StrTuple param = getTwoParamether();
	try {
		findHierarchy(param.first); //will throw if not exist
		std::cout << "Hierarchy with name " << param.first << " already exists in the database. No changes were made.\n";
		return;
	}
	catch (const int&) {} //does not exist

	string data;
	if (param.second.empty()) {
		std::cout << "File name not found. Reading data from console:\n";
		try {
			data = readFromConsole();
		}
		catch (const std::bad_alloc&) {
			std::cerr << "Error: Input data could not be loaded due to possible lack of memory for the operation.\n";
			return;
		}
		catch (...) {
			std::cerr << "Error:Input data could not be loaded due to unexpected problem.\n";
			return;
		}
	}
	else {
		try {
			data = (readFromFile(param.second));
		}
		catch (const FileCantLoad&) {
			std::cerr << "Error: File " << param.second << " could not be opened. No changes were made.\n";
			return;
		}
		catch (const std::bad_alloc&) {
			std::cerr << "Error: File data could not be loaded due to possible lack of memory for the operation.\n";
			return;
		}
		catch (...) {
			std::cerr << "Error: File data could not be loaded due to unexpected problem.\n";
			return;
		}
	}
	Hierarchy* newHier = nullptr;
	try {
		newHier = new Hierarchy(data + '\n', param.first);
		//newHier->setName(param.first);
	}
	catch (const std::bad_alloc&) {
		std::cerr << "Error: Hierarchy could not be created due to possible lack of memory for the operation.\n";
		return;
	}
	catch (const std::logic_error& e) {
		std::cerr << "Error: Hierarchy could not be created due to incorrect data. " << e.what()<<std::endl;
		return;
	}
	catch (...) {
		std::cerr << "Error: Hierarchy could not be created due to unexpected problem.\n";
		return;
	}
	hierarchies.insert(std::move(*newHier));
	delete newHier;
	std::cout << "(" << param.first << " was loaded.)\n";
}

void FrontEnd::save()
{
	StrTuple param = getTwoParamether();
	string data;
	try {
		Hierarchy* hier = findHierarchy(param.first);

		if (param.second.empty()) {
			std::cout << "(" << param.first << " data )\n";
			std::cout << hier->print();
		}
		else {
			try {
				data = hier->print();
				writeInFile(param.second, data);
			}
			catch (const std::exception&) {
				std::cerr << "Error: Writing in " << param.second << " failed due to unexpected problem.\nData might not be saved in the file.\n";
			}
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::find()
{
	StrTuple param = getTwoParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);

		if (hier->find(param.second)) {
			std::cout << param.second << " exists in " << param.first << std::endl;
		}
		else {
			std::cout << param.second << " was NOT found in " << param.first << std::endl;
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::num_subordinates()
{
	StrTuple param = getTwoParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);

		int number = hier->num_subordinates(param.second);
		if (number < 0) {
			std::cout << "Worker " << param.second << " was not found in " << param.first << std::endl;
		}
		else {
			std::cout << param.second << " has " << number << " subordinates\n";
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::manager()
{
	StrTuple param = getTwoParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);

		string name = hier->manager(param.second);
		if (name == "")
		{
			std::cout << "Worker's manager was not found\n";
		}
		else {
			std::cout << "The manager of " << param.first << " is " << name << std::endl;
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::num_employees()
{
	string param = getOneParamether();
	try {
		Hierarchy* hier = findHierarchy(param);

		int employees = hier->num_employees();
		std::cout << "There " << (employees == 1 ? "is " : "are ") << hier->num_employees()
			<< (employees == 1 ? " employee " : " employees ") << " in " << param << std::endl;

	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param << " was not found.\n";
		return;
	}
}

void FrontEnd::num_overloaded()
{
	string param = getOneParamether();
	try {
		Hierarchy* hier = findHierarchy(param);

		std::cout << hier->num_overloaded() << std::endl;

	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param << " was not found.\n";
		return;
	}
}

void FrontEnd::fire()
{
	StrTuple param = getTwoParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);
		if (!hier) {
			std::cout << "Hierarchy with name " << param.first << " was not found.\n";
			return;
		}
		if (hier->fire(param.second)) {
			std::cout << param.second << " was fired from " << param.first << std::endl;
		}
		else if (param.second == "Uspeshnia") {
			std::cout << param.second << " is the boss and can not be fired!\n";
		}
		else {
			std::cout << param.second << " was not found in " << param.first << std::endl;
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::hire()
{
	StrTuple param = getThreeParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);

		if (hier->hire(param.second, param.third)) {
			std::cout << param.second << " was hired by " << param.third << std::endl;
		}
		else {
			std::cout << param.third << " was not found in " << param.first << std::endl;
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::join()
{
	StrTuple param = getThreeParamether();
	Hierarchy* hier1 = nullptr;
	Hierarchy* hier2 = nullptr;
	try {
		findHierarchy(param.third); //will throw if not exist
		std::cout << "Hierarchy with name " << param.third << " already exists in the database. No changes were made.\n";
		return;
	}
	catch (const int&) {} //does not exist

	try {
		hier1 = findHierarchy(param.first);
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
	try {
		hier2 = findHierarchy(param.second);
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.second << " was not found.\n";
		return;
	}

	Hierarchy* newHier = nullptr;
	try {
		newHier = new Hierarchy(std::move(hier1->join(*hier2)), param.third);
	}
	catch (const OutOfMemory& e) {
		std::cout << e.what() << std::endl;
		return;
	}
	catch (...) {
		std::cout << "Error: Operation could not be completed.\n";
		return;
	}

	hierarchies.insert(std::move(*newHier));
	delete newHier;
	std::cout << param.third << " was successfully created from " << param.first << " and " << param.second << std::endl;

}

void FrontEnd::salary()
{
	StrTuple param = getTwoParamether();
	try {
		Hierarchy* hier = findHierarchy(param.first);

		int salary = hier->getSalary(param.second);
		if (salary < 0) {
			std::cout << "Worker " << param.second << " was not found in " << param.first << std::endl;
		}
		else {
			std::cout << salary << std::endl;
		}
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param.first << " was not found.\n";
		return;
	}
}

void FrontEnd::incorporate()
{
	string param = getOneParamether();
	try {
		Hierarchy* hier = findHierarchy(param);

		hier->incorporate();
		std::cout << param << " was incorporated\n";
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param << " was not found.\n";
		return;
	}
}

void FrontEnd::modernize()
{
	string param = getOneParamether();
	try {
		Hierarchy* hier = findHierarchy(param);

		hier->modernize();
		std::cout << param << " was modernized\n";
	}
	catch (const int&) {//not found
		std::cout << "Hierarchy with name " << param << " was not found.\n";
		return;
	}
}
