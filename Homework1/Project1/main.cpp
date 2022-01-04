#include "TimeLine.h"
#include <limits>//numeric_limits

#pragma region Input functions

void fixCin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void getCountInput(int& workerCount, int& clientsCount)
{
	do {
		if (!std::cin) {
			fixCin();
			std::cout << "Please,input a number.\n";
		}
		std::cout << "Workers count: ";
		std::cin >> workerCount;
	} while (!std::cin || workerCount < 0);
	//
	do {
		if (!std::cin) {
			fixCin();
			std::cout << "Please,input a number.\n";
		}
		std::cout << "Clients count: ";
		std::cin >> clientsCount;
	} while (!std::cin || clientsCount < 0);
}

bool getClientsInput(std::vector<Client>& clients, const int count)
{
	Client tempClient;
	std::cout << "Clients info:\n";
	std::cout << "Arrive Minute | Banana Quantity | Schweppes Qauntity | Max wait time\n";
	for (int i = 0; i < count; i++) {
		try {
			std::cin >> tempClient.arriveMinute >> tempClient.banana >> tempClient.schweppes >> tempClient.maxWaitTime;
		}
		catch (const std::exception&) {
			std::cout << "Error: Invalid information. Please, enter it again.\n";
			--i;
			fixCin();
			continue;
		}
		try {
			clients.push_back(tempClient);
		}
		catch (const std::bad_alloc&) {
			std::cout << "Error: There was a problem with memory allocation. Program can't continue it's work.\n";
			return false;
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what();
			return false;
		}
	}
	return true;
}

#pragma endregion

int main() {
	//data
	Store* store = createStore();
	std::vector<Client> clients;
	int workerCount = 0;
	int clientsCount = 0;
	int timeLimit;
	//
	//input
	getCountInput(workerCount, clientsCount);
	if (!getClientsInput(clients, clientsCount)) {
		delete store;
		return -1;
	}
	//
	ActionPrinter* printer = new ActionPrinter();
	store->setActionHandler(printer);
	//
	//Additional functionality
	/*std::cout << "\nWould you like to see the information to a certain minute of the day? If not, input a negative value for the full information:";
	try {
		std::cin >> timeLimit;
	}
	catch (...) {
		std::cout << "Invalid type, all information will be displayed.\n";
		timeLimit = -1;
	}*/
	timeLimit = -1;
	//
	std::cout << "----------------------------------------------------\n";
	store->init(workerCount,0,0);
	store->addClients(clients.data(), clientsCount);
	store->advanceTo(timeLimit);
	//
	//delete section
	delete store;
	delete printer;
	return 0;
}
