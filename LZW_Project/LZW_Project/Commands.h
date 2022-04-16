#pragma once
#include <string>


/// @brief Recognize which command is being executed
enum class CommandOption {
	_invalid = -1,
	_using,//0 -Will remember file name
	_zip,//1
	_unzip,//2
	_info,//3
	_refresh,//4
	_ec,//5
	_help,//6
	_show,//7 -Shows _using saved file
	_exit,//8
	_add,//9
	_remove//10
};

//Using + zip name
//ZIP + new archive name
//UNZIP + archive_name (if not - using one is used) //as later param will be used ALL or specific file name
//Refresh + file to refresh
//EC to go through all files and check the security encoding

struct StrTuple {
	std::string first;
	std::string second;
	std::string third;
};

class Commands {

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

	Commands() = default;
	/// @brief Constructor taking a command line that separates the commands after being constructed.
	/// @param line Command line consisting of command and parameters.
	Commands(std::string line);
	/// @brief Default destructor.
	virtual ~Commands() = default;
	/// @brief Calls separateCommand()
	/// @see Command::separateCommand(std::string& str)
	/// @param line String to be processed.
	void processCommand(std::string line);
	/// @brief Returns the command after being processed.
	/// @return Command enum.
	CommandOption getCommand() const;
	/// @brief Returns command paramether for commands with just one paramether 
	std::string getOneParamether();
	/// @brief Returns structure of up to three strings that contains the first and the second value of command parameters. 
	StrTuple getTwoParamether();
	/// @brief Returns structure of up to three strings that contains the first ,the second and the third value of command parameters.
	StrTuple getThreeParamether();
};
