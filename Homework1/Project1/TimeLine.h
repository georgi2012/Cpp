#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "interface.h"
#include "Event.h"
#include "ActionPrinter.h"
#include "EventsQueue.h"

using std::vector;

class TimeLine :public Store {
private:
	//
#pragma region Constants
	static const int DELIVERY_TIME = 60;
	static const int DELIVERY_VALUE = 100;
#pragma endregion
	//
#pragma region Data Variables
	int availableBananas = 0;//currently available in the store
	int availableSchweppes = 0;//currently available in the store
	int availWorkerCount = 0;//currently available for sending
	//int expectedBananas = 0;//Bananas that are expected to be delivered with workers that are already sent 
	//int expectedDrinks = 0;//Schweppes that are expected to be delivered with workers that are already sent
	//^Optimization idea so that promissed products to waiting clients are taken into consideration
	int orderedBananas = 0;//Number of ordered by workers bananas atm. >= expectedBananas
	int orderedDrinks = 0;//Number of ordered by workers schweppes atm. >= expectedDrinks
	unsigned minutes = 0; //current minute of the day
	unsigned allClientsNum = 0; //all registered clients for the day . Used for their indexation
	Events_Queue<Event*> events; //known events sorted by time and priority
	Queue<Client> clients; //clients, received by input
	ActionHandler* actionHandler = nullptr;
	vector<Event_ClientCome> waiting;//clients who have arrived but were not served yet.  
#pragma endregion
	//
#pragma region Private functions for work with the data
	void fillTimeline(const int until = -1);//The function that fills and process events through the other functions
	bool haveWantedProductsFor(int banana, int drink) const;//If we can surve the client
	void onWorkerReturn();//Change product balances ,worker count
	void onClientCome();//Serving or sending workers and leaving him to wait
	void onClientLeave();//If his ID is still in the waiting vector, he takes whatever he can and leaves
	void serveWaitingClient();//After worker return we can check if we can serve waiting clients
#pragma endregion
	//
public:
	//
#pragma region Constructors
	TimeLine() = default;
	~TimeLine();
#pragma endregion
	//
#pragma region Functions Inherited from Store
	//store override
	virtual void init(int workerCount, int startBanana, int startSchweppes = 0) override;
	virtual void setActionHandler(ActionHandler* handler) override;
	virtual void addClients(const Client* clients, int count) override;
	virtual void advanceTo(int minute) override;
	virtual int getBanana() const override;
	virtual int getSchweppes() const override;
#pragma endregion
	//
};