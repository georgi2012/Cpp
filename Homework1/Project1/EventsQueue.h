#pragma once
#include "Queue.h"
#include "Event.h"

//Priority queue from Aliexpress. Use Heap for max performance

template <typename T>
class Events_Queue :public Queue<Event*> {
private:
	//queue that adds new elements in a sorted way by time and priority
	bool isAheadInTimeline(const Event* a, const Event* b) {
		return !b || (a->getMin() > b->getMin()) //by minutes
			      || (a->getMin() == b->getMin() && (int)a->getType() > (int)b->getType()) //by event when minutes are equal
			      || (a->getType() == EventType::WorkerReturn && b->getType() == EventType::WorkerReturn && //by resourse when event is equal
				     (int)dynamic_cast<const Event_WorkerReturn&>(*a).getResourceType() > (int)dynamic_cast<const Event_WorkerReturn&>(*b).getResourceType());
	}

public:
	Events_Queue() = default;
	~Events_Queue() = default;

	void push_back(const T& newObj) {
		Node* newNode = new Node(newObj);

		++nodesSize;
		if (!first) {
			first = newNode;
			last = newNode;
			return;
		}
		Node* curNode = first;
		if (!isAheadInTimeline(newObj, curNode->data))
		{
			newNode->next = first;
			first = newNode;
		}
		else
		{
			while (curNode->next && isAheadInTimeline(newObj, curNode->next->data))
			{
				curNode = curNode->next;
			}
			newNode->next = curNode->next;
			curNode->next = newNode;
		}
	}

};