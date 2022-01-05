#include "FrontEnd.h"
#include <iostream>

int main() {

	FrontEnd processor;
	bool isWorking = true;
	string input;
	std::cout << "Type help for commands.\n";
	std::cout << "-------------------------------------------\n";

	while (isWorking) {
		std::cout << ">";
		getline(std::cin, input);
		try {
			processor.executeCommand(input);
		}
		catch (const ExitProgram& e) {
			std::cout << e.what() << std::endl;
			isWorking = false;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}