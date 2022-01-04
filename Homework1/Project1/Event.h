#pragma once


enum class EventType {
	Invalid = -1,
	WorkerLeave,
	WorkerReturn,
	ClientCome,
	ClientLeave
};

//should these be sctructures?
class Event {
private:
	EventType type;
	unsigned minutes;
public:
	Event(EventType type,unsigned mins) :type(type),minutes(mins){}
	virtual EventType getType() const{
		return type;
	}
	virtual unsigned getMin() const{
		return minutes;
	}
};


class Event_WorkerLeave :public Event{
private:
	//unsigned returnMins;
	ResourceType resource;
public:
	Event_WorkerLeave(unsigned min, ResourceType res) :Event(EventType::WorkerLeave,min), resource(res){}
	
	ResourceType getResourceType() const { return resource; }
};


class Event_WorkerReturn :public Event {
private:
	//unsigned returnMins;
	ResourceType resource;
public:
	Event_WorkerReturn(unsigned min, ResourceType res) :Event(EventType::WorkerReturn, min), resource(res) {}

	ResourceType getResourceType() const { return resource; }
};


class Event_ClientCome :public Event {
private:
	//unsigned returnMins;
	int bananas;
	int drinks;
	int number;
	
public:
	Event_ClientCome(unsigned min, int num,int bananas , int drinks) :Event(EventType::ClientCome, min), bananas(bananas),drinks(drinks),number(num)
	{}
	int getWantedBananas() const { return bananas; } 
	int getWantedDrinks() const { return drinks; }
	int getIndex() const { return number; }
};

class Event_ClientLeave :public Event {
private:
	//unsigned returnMins;
	int bananas;
	int drinks;
	int number;
public:
	Event_ClientLeave(unsigned min,int num, int bananas, int drinks) :Event(EventType::ClientLeave, min), bananas(bananas), drinks(drinks),number(num) {}
	int getWantedBananas() const { return bananas; }
	int getWantedDrinks() const { return drinks; }
	int getIndex() const { return number; }
};

