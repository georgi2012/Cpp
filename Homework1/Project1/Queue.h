#pragma once
#include <stdexcept>

template <typename T>
class Queue {
protected:
	//data
	struct Node {
		T data;
		Node* next;
		Node(const T& data, Node* next = nullptr)
			:data(data), next(next) {}
	} *first = nullptr, * last = nullptr;
	size_t nodesSize = 0;
	//
public:
	Queue() = default;

	const T& front() {
		if (nodesSize > 0) {
			return first->data;
		}
		throw std::bad_exception();
	}

	void pop_front() {
		if (nodesSize > 0) {
			Node* popped = first;
			first = first->next;
			delete popped;
			--nodesSize;
		}
	}

	virtual void push_back(const T& newObj) {
		Node* newNode = new Node(newObj);
		if (nodesSize == 0) {
			first = newNode;
		}
		else {
			last->next = newNode;
		}
		last = newNode;
		++nodesSize;
	}

	size_t size() {
		return nodesSize;
	}

	bool empty() {
		return nodesSize == 0;
	}

	virtual ~Queue() {
		Node* curNode = first;
		Node* nextNode = nullptr;
		while (curNode) {
			nextNode = curNode->next;
			delete curNode;
			curNode = nextNode;
		}
		first = last = nullptr;
		nodesSize = 0;
	}
};