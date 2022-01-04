#pragma once
#include "interface.h"
#include <iostream>

class ActionPrinter :public ActionHandler {

	// Inherited via ActionHandler
	virtual void onWorkerSend(int minute, ResourceType resource) override;

	virtual void onWorkerBack(int minute, ResourceType resource) override;

	virtual void onClientDepart(int index, int minute, int banana, int schweppes) override;

};