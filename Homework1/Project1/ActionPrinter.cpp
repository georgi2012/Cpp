#include "ActionPrinter.h"

void ActionPrinter::onWorkerSend(int minute, ResourceType resource)
{
	std::cout << "W " << minute << (resource == ResourceType::banana ? " banana" : " schweppes") << std::endl;
}

void ActionPrinter::onWorkerBack(int minute, ResourceType resource)
{
	std::cout << "D " << minute << (resource == ResourceType::banana ? " banana" : " schweppes") << std::endl;
}

void ActionPrinter::onClientDepart(int index, int minute, int banana, int schweppes)
{
	std::cout << index << " " << minute << " " << banana << " " << schweppes << std::endl;
}
