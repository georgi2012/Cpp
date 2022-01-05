#pragma once
#include <iostream>
#include <string>

/// @brief Recognize which command is being executed
enum class CommandOption {
	_invalid = -1,
	_load,//0
	_save,//1
	_find,//2
	_num_subordinates,//3
	_manager,//4
	_num_employees,//5
	_overloaded,//6
	_join,//7
	_help,//8
	_fire,//9
	_hire,//10
	_salary,//11
	_incorporate,//12
	_modernize,//13
	_exit//14
};

struct StrTuple {
	std::string first;
	std::string second;
	std::string third;
};

class Command {

private:
	/// @brief Command parameters
	std::string parameter;
	/// @brief The command that is being processed. Set to _invalid by default.
	CommandOption cmdOpt = CommandOption::_invalid;
	/// @brief Separates command from parameters.
	/// @param str Includes both the command and all parameters.
	void separateCommand(std::string& str);
	/// @brief Recognizes the command .
	/// @param str The command name string without parameters.
	/// @return Command enum number.
	CommandOption switchCommandString(std::string& str);
	/// @brief Capitalizes all letters.
	/// @param str String to be capitalized.
	void capitalizeCommand(std::string& str);
public:

	Command() = default;
	/// @brief Constructor taking a command line that separates the commands after being constructed.
	/// @param line Command line consisting of command and parameters.
	Command(std::string line);
	/// @brief Default destructor.
	virtual ~Command() = default;
	/// @brief Calls separateCommand()
	/// @see Command::separateCommand(std::string& str)
	/// @param line String to be processed.
	void processCommand(std::string line);
	/// @brief Returns the command after being processed.
	/// @return Command enum.
	CommandOption getCommand() const;
	/// @brief Returns command paramether for commands with just one paramether 
	std::string getOneParamether();
	/// @brief Returns structure of up to three strings that contains the first and the second value of command parameters. Second parameter can be address in quotes
	StrTuple getTwoParamether();
	/// @brief Returns structure of up to three strings that contains the first ,the second and the third value of command parameters.
	StrTuple getThreeParamether();
};
