#include "Commands.h"

void Commands::separateCommand(std::string& str)
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

CommandOption Commands::switchCommandString(std::string& str)
{
	capitalizeCommand(str);
	if (str == "USING")
	{
		return CommandOption::_using;
	}
	if (str == "ZIP")
	{
		return CommandOption::_zip;
	}
	if (str == "UNZIP")
	{
		return CommandOption::_unzip;
	}
	if (str == "INFO")
	{
		return CommandOption::_info;
	}
	if (str == "REFRESH")
	{
		return CommandOption::_refresh;
	}
	if (str == "EC")
	{
		return CommandOption::_ec;
	}
	if (str == "HELP")
	{
		return CommandOption::_help;
	}
	if (str == "EXIT")
	{
		return CommandOption::_exit;
	}
	if (str == "SHOW")
	{
		return CommandOption::_show;
	}
	if (str == "ADD")
	{
		return CommandOption::_add;
	}
	if (str == "REMOVE")
	{
		return CommandOption::_remove;
	}
	return CommandOption::_invalid;

}

void Commands::capitalizeCommand(std::string& str)
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

Commands::Commands(std::string line)
{
	separateCommand(line);
}

void Commands::processCommand(std::string line)
{
	separateCommand(line);
}

CommandOption Commands::getCommand() const
{
	return cmdOpt;
}

std::string Commands::getOneParamether()
{
	unsigned i = 0;
	while (i < parameter.size() && parameter[i] != ' ') {
		++i;
	}
	return parameter.substr(0, i);
}

StrTuple Commands::getTwoParamether()
{
	if (parameter.empty()) {
		return StrTuple();
	}
	std::string frstArg;
	unsigned i = 0;

	while (i < parameter.size() && parameter[i] != ' ') {
		i++;
	}
	frstArg = parameter.substr(0, i);
	while (i < parameter.size() && parameter[i] == ' ') {//spaces between first and second
		i++;
	}

	unsigned j = 0;
	while (j + i < parameter.size() && parameter[j + i] != ' ') {//second word
		j++;
	}
	
	return StrTuple{ frstArg, parameter.substr(i,j) };
}

StrTuple Commands::getThreeParamether()
{
	if (parameter.empty()) {
		return StrTuple();
	}
	StrTuple twoParam = getTwoParamether();
	std::string param;
	unsigned i = parameter.size() - 1;
	int spaces = 0;
	while (i > 0 && parameter[i] == ' ') {//spaces
		--i;
		++spaces;
	}
	while (i > 0 && parameter[i] != ' ') {//word
		--i;
	}
	param = parameter.substr(i + 1, parameter.size() - i - spaces - 1); //second param
	return StrTuple{ twoParam.first, twoParam.second,param };

}
