#include "TimeLine.h"


void TimeLine::init(int workerCount, int startBanana, int startSchweppes)
{
	availableBananas = startBanana;
	availableSchweppes = startSchweppes;
	availWorkerCount = workerCount;
}

void TimeLine::setActionHandler(ActionHandler* handler)
{
	actionHandler = handler;
}

void TimeLine::addClients(const Client* clients, int count)
{
	if (count < 0)
	{
		throw std::invalid_argument("addClient: count can't be negative");
	}
	for (int i = 0; i < count; i++)
	{
		this->clients.push_back(clients[i]);
	}
	allClientsNum += count;
}

void TimeLine::advanceTo(int minute)
{
	fillTimeline(minute);
}

int TimeLine::getBanana() const
{
	return availableBananas;
}

int TimeLine::getSchweppes() const
{
	return availableSchweppes;
}

TimeLine::~TimeLine()
{
	while (!events.empty()) {
		delete events.front();
		events.pop_front();
	}
}

bool TimeLine::haveWantedProductsFor(int banana, int drink) const {
	return  banana <= availableBananas && drink <= availableSchweppes;
}

void TimeLine::serveWaitingClient()
{
	int index = 0;
	for (; index < waiting.size(); index++)
	{//first we serve the clients that we can send away
		if (haveWantedProductsFor(waiting[index].getWantedBananas(), waiting[index].getWantedDrinks())) {
			availableBananas -= waiting[index].getWantedBananas();
			availableSchweppes -= waiting[index].getWantedDrinks();
			//std::cout << "Client " << waiting[index].getIndex() << " " << minutes << " " << waiting[index].getWantedBananas() << " " << waiting[index].getWantedDrinks() << std::endl;
			if (actionHandler) {
				actionHandler->onClientDepart(waiting[index].getIndex(), minutes, waiting[index].getWantedBananas(), waiting[index].getWantedDrinks());
			}
			
			waiting.erase(waiting.begin()+index);


		}
	}
}

void TimeLine::onWorkerReturn() {

	Event_WorkerReturn& client = dynamic_cast<Event_WorkerReturn&>(*events.front());
	minutes = client.getMin();
	//std::cout << "D " << client.getMin() << (client.getResourceType() == ResourceType::banana ? " banana" : " schweppes") << std::endl;
	if (actionHandler)
	{
		actionHandler->onWorkerBack(minutes, ((client.getResourceType() == ResourceType::banana ? ResourceType::banana : ResourceType::schweppes)));
	}
	if (client.getResourceType() == ResourceType::banana)
	{
		availableBananas += DELIVERY_VALUE;
		orderedBananas -= DELIVERY_VALUE;
		//expectedBananas = expectedBananas >= orderedBananas ? orderedBananas : expectedBananas;
	}
	else
	{
		availableSchweppes += DELIVERY_VALUE;
		orderedDrinks -= DELIVERY_VALUE;
		//expectedDrinks = expectedDrinks >= orderedDrinks ? orderedDrinks : expectedDrinks;
	}
	//check if we can serve some of the waiting 
	++availWorkerCount;

	delete events.front();
	events.pop_front();

	if (!events.empty() && events.front()->getType() == EventType::WorkerReturn)
	{
		onWorkerReturn();
	}
}

void TimeLine::onClientCome() {
	Event_ClientCome& client = dynamic_cast<Event_ClientCome&>(*events.front());
	minutes = client.getMin();
	if (haveWantedProductsFor(client.getWantedBananas(), client.getWantedDrinks()))//allAreProcessed(waiting) &&
	{//we can sell it right now
		//std::cout << "Client " << client.getIndex() << " " << client.getMin() << " " << client.getWantedBananas() << " " << client.getWantedDrinks() << std::endl;
		if (actionHandler) {
			actionHandler->onClientDepart(client.getIndex(), client.getMin(), client.getWantedBananas(), client.getWantedDrinks());
		}
		availableBananas -= client.getWantedBananas();
		availableSchweppes -= client.getWantedDrinks();
	}
	else if (availWorkerCount > 0) {//we can send a worker
		int bananasNeeded = client.getWantedBananas() - availableBananas- orderedBananas;
		int drinksWanted = client.getWantedDrinks() - availableSchweppes -orderedDrinks;
		int sentForBananas = 0; //so we can report banana workers send first and then for drinks and still send more workers for the most needed product
		int sentForDrinks = 0;

		if (bananasNeeded > 0 || drinksWanted > 0) {//needs worker to be send
			bool drinksAreWantedMore = drinksWanted > bananasNeeded;
			int neededWorkers = ceil((drinksAreWantedMore ? drinksWanted : bananasNeeded) / (double)DELIVERY_VALUE);
			for (int i = 0; i < (availWorkerCount > neededWorkers ? neededWorkers : availWorkerCount); i++)
			{
				
				events.push_back(new Event_WorkerReturn(client.getMin() + DELIVERY_TIME, drinksAreWantedMore ? ResourceType::schweppes : ResourceType::banana));
				if (drinksAreWantedMore) {
					++sentForDrinks;
					orderedDrinks += DELIVERY_VALUE;
				}
				else {
					++sentForBananas;
					orderedBananas += DELIVERY_VALUE;
				}
			}
			//now check for the second wanted
			availWorkerCount = availWorkerCount < neededWorkers ? 0 : (availWorkerCount - neededWorkers);
			neededWorkers = ceil((!drinksAreWantedMore ? drinksWanted : bananasNeeded) / (double)DELIVERY_VALUE);
			for (int i = 0; i < (availWorkerCount > neededWorkers ? neededWorkers : availWorkerCount); i++)
			{
				//std::cout << "W " << client.getMin() << (!drinksAreWantedMore ? " schweppes" : " bananas") << std::endl;
		
				events.push_back(new Event_WorkerReturn(client.getMin() + DELIVERY_TIME, !drinksAreWantedMore ? ResourceType::schweppes : ResourceType::banana));
				if (!drinksAreWantedMore) {
					++sentForDrinks;
					orderedDrinks += DELIVERY_VALUE;
				}
				else {
					++sentForBananas;
					orderedBananas += DELIVERY_VALUE;
				}
			}
			if (actionHandler) {
				for (int i = 0; i < sentForBananas; i++) {
					actionHandler->onWorkerSend(minutes,ResourceType::banana);
				}
				for (int i = 0; i < sentForDrinks; i++) {
					actionHandler->onWorkerSend(minutes, ResourceType::schweppes);
				}
			}
			//now check for the second wanted
			availWorkerCount = availWorkerCount < neededWorkers ? 0 : (availWorkerCount - neededWorkers);

			//expectedBananas -= client.getWantedBananas() - client.bananasLeftWanted; //taken fron wanted
			//expectedDrinks -= client.getWantedDrinks() - client.drinksLeftWanted;
		}
		//else {//no worker should be send , we have the resouces or we have send a worker already
		//}
		
		waiting.push_back(client);
	}
	else {
		//it will have to wait
		waiting.push_back(client);
	}

	delete events.front();
	events.pop_front();
}

void TimeLine::onClientLeave() {

	Event_ClientLeave& client = dynamic_cast<Event_ClientLeave&>(*events.front());
	for (int i = 0; i < waiting.size(); i++) {
		if (waiting[i].getIndex() == client.getIndex())
		{//if his waiting time has ran out , then it should be in the waiting list
			//if he is not => he has been served already and has left-> just remove him from the vector
			//we will take whatever he can of his order
			minutes = client.getMin();

			int bananasTaken = client.getWantedBananas() > availableBananas ? availableBananas : client.getWantedBananas();
			int drinksTaken = client.getWantedDrinks() > availableSchweppes ? availableSchweppes : client.getWantedDrinks();
			
			availableBananas -= bananasTaken;
			availableSchweppes -= drinksTaken;
			//std::cout << "Client " << client.getIndex() << " " << minutes << " " << bananasTaken << " " << drinksTaken << std::endl;
			if (actionHandler) {
				actionHandler->onClientDepart(client.getIndex(), minutes, bananasTaken, drinksTaken);
			}
			waiting.erase(waiting.begin() + i);
			break;
		}
	}
	delete events.front();
	events.pop_front();
}

void TimeLine::fillTimeline(const int until) {
	if (clients.empty())
	{
		return;
	}

	bool processAll = until < 0;
	if (events.empty()) {
		events.push_back(new Event_ClientCome(clients.front().arriveMinute, 0, clients.front().banana, clients.front().schweppes));
		events.push_back(new Event_ClientLeave(clients.front().arriveMinute + clients.front().maxWaitTime, 0, clients.front().banana, clients.front().schweppes));
		clients.pop_front();
	}

	while (!events.empty() || !clients.empty())
	{
		if (!clients.empty() && (events.empty() || clients.front().arriveMinute < events.front()->getMin()))
		{
			events.push_back(new Event_ClientCome(clients.front().arriveMinute, allClientsNum - clients.size(), clients.front().banana, clients.front().schweppes));
			events.push_back(new Event_ClientLeave(clients.front().arriveMinute + clients.front().maxWaitTime, allClientsNum - clients.size(), clients.front().banana, clients.front().schweppes));
			clients.pop_front();
		}

		if (!processAll && until < events.front()->getMin())
		{
			break;
		}

		switch (events.front()->getType())
		{
		case EventType::ClientCome: {
			onClientCome();
			//
			break;
		}
		case EventType::ClientLeave: {
			onClientLeave();

			break;
		}

		case EventType::WorkerReturn: {
			onWorkerReturn();
			serveWaitingClient();

			break;
		}

		default: throw std::invalid_argument("Timeline invalid event");
			break;
		}


	}
}

Store* createStore() {
	return (new TimeLine());
}

