#include "Interface.h"
#include <sstream>

//! C++17 or later is needed for filestream library !

int main()
{
	Interface inter;
	std::string command;
	bool end = false;
	std::cout << "To get commands and rules type Help.\n";
	while (!end) {
		std::cout << ">";
		std::getline(std::cin, command);
		try {
			inter.executeCommand(command);
		}
		catch (const ExitProgram& e) {
			std::cout << e.what();
			end = true;
		}
		catch (const std::bad_alloc&) {
			std::cout << "Error : There was not enough memory to finish that operation!\n";
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
		catch (...) {
			std::cout << "Error : Unexpected problem occured!\n";
		}
	}

	return 0;
}