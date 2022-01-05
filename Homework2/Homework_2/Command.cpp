#include "Command.h"

void Command::separateCommand(std::string& str)
{
	unsigned i = 0;
	while (i < str.size() && str[i] == ' ') { //remove empty spaces before command
		i++;
	}
	str = str.substr(i);
	i = 0;
	while (i < str.size() && str[i] != ' ') { //get command
		i++;
	}
	parameter = str.substr(0, i);//just reusing a variable
	cmdOpt = switchCommandString(parameter); //recognize command
	if (i < str.size()) {
		while (i < str.size() && str[i] == ' ') {//no spaces
			i++;
		}
		parameter = str.substr(i);
	}
}

CommandOption Command::switchCommandString(std::string& str)
{
	capitalizeCommand(str);
	if (str == "SAVE")
	{
		return CommandOption::_save;
	}
	if (str == "LOAD")
	{
		return CommandOption::_load;
	}
	if (str == "FIND")
	{
		return CommandOption::_find;
	}
	if (str == "NUM_SUBORDINATES")
	{
		return CommandOption::_num_subordinates;
	}
	if (str == "MANAGER")
	{
		return CommandOption::_manager;
	}
	if (str == "NUM_EMPLOYEES")
	{
		return CommandOption::_num_employees;
	}
	if (str == "HELP")
	{
		return CommandOption::_help;
	}
	if (str == "EXIT")
	{
		return CommandOption::_exit;
	}
	if (str == "OVERLOADED")
	{
		return CommandOption::_overloaded;
	}
	if (str == "JOIN")
	{
		return CommandOption::_join;
	}
	if (str == "FIRE")
	{
		return CommandOption::_fire;
	}
	if (str == "HIRE")
	{
		return CommandOption::_hire;
	}
	if (str == "SALARY")
	{
		return CommandOption::_salary;
	}
	if (str == "INCORPORATE")
	{
		return CommandOption::_incorporate;
	}
	if (str == "MODERNIZE")
	{
		return CommandOption::_modernize;
	}
	return CommandOption::_invalid;

}

void Command::capitalizeCommand(std::string& str)
{
	unsigned i = 0;
	while (i < str.size())
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] += 'A' - 'a';
		}
		i++;
	}
}

Command::Command(std::string line)
{
	separateCommand(line);
}

void Command::processCommand(std::string line)
{
	separateCommand(line);
}

CommandOption Command::getCommand() const
{
	return cmdOpt;
}

//
//std::string Command::getSaveAsPath()//without quotes
//{
//	if (parameter.back() == ' ') //in case there are spaces after path string
//	{
//		int i = parameter.size() - 1;
//		while (i >= 0 && parameter[i] == ' ')
//		{
//			i--;
//		}
//		parameter.erase(i + 1, parameter.size() - i);
//	}
//	if (parameter.size() >= 2 && parameter.front() == '"' && parameter.back() == '"') {
//		parameter = parameter.substr(1, parameter.size() - 2);
//	}
//	return parameter;
//}


std::string Command::getOneParamether()
{
	unsigned i = 0;
	while (i < parameter.size() && parameter[i] != ' ') {
		++i;
	}
	return parameter.substr(0,i);
}

StrTuple Command::getTwoParamether()
{
	if (parameter.empty()) {
		return StrTuple();
	}
	std::string frstArg;
	unsigned i = 0;
	bool isQuoted = false;
	bool removeQuotes = false;
	while (i < parameter.size() && parameter[i] != ' ') {
		i++;
	}
	frstArg = parameter.substr(0, i);
	while (i < parameter.size() && parameter[i] == ' ') {//spaces between first and second
		i++;
	}

	unsigned j = 0;
	while (j+i < parameter.size() && (parameter[j + i] != ' ' || isQuoted)) {//second word
		if (parameter[j+i] == '\"') {
			if (isQuoted)
				removeQuotes = true; //we have at least 2 quotes in our string
			isQuoted = !isQuoted;
		}
		j++;
	}
	if (removeQuotes) {//remove last and first
		return StrTuple{ frstArg, parameter.substr(i+1,j-2) };
	}
	return StrTuple{ frstArg, parameter.substr(i,j) };
}

StrTuple Command::getThreeParamether()
{
	if (parameter.empty()) {
		return StrTuple();
	}
	StrTuple twoParam = getTwoParamether();
	std::string param;
	unsigned i = parameter.size() - 1;
	int spaces = 0;
	while (i > 0 && parameter[i]==' ') {//spaces
		--i;
		++spaces;
	}
	while (i > 0 && parameter[i] != ' ') {//word
		--i;
	}
	param = parameter.substr(i+1, parameter.size()-i-spaces-1); //second param
	return StrTuple{ twoParam.first, twoParam.second,param };

}
