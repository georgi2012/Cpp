#pragma once
#include <iostream>
//#include <string>
#include <functional>



using std::size_t;
using std::hash;

/// @brief unordered_map that uses hash to access it's element fast. Elements are linked lists and collision items are added in it. 
/// @tparam K Type of Key element that will be used for searching .
/// @tparam T Type of value element that will be stored in the class.
template<class K, class T>
class Unordered_map {
public:
	/// @brief Linked list
	struct ll {
		K key;
		T value;
		ll* next = nullptr;
	};
private:
	/// @brief Bucket size can be allocated dynamically for better performance depending on the expected number of inputs. In it's used default constructor, min_size will be allocated
	static const unsigned min_size = 1000;
	/// @brief If it is tried to request more size for buckets, it will be limited to up to that number
	static const unsigned max_limit_size = 100'019;// is prime

	/// @brief Buckets of lists
	ll** arr = nullptr;
	/// @brief Number of unique elements 
	size_t size = 0;
	/// @brief Allocated buckets
	size_t max_size = 0;
	//
	void clearList(ll* current) {
		if (current->next) {
			clearList(current->next);
		}
		delete current;
	}

	void allocateMemory(size_t capacity)
	{
		if (capacity > max_limit_size) capacity = max_limit_size;
		try {
			arr = new ll * [capacity];
			for (size_t i = 0; i < capacity; i++)
			{
				arr[i] = nullptr;
			}
		}
		catch (const std::bad_alloc& e)
		{//failed
			if (capacity < 10) {//probably too low to operate
				throw;
			}
			allocateMemory(capacity / 2);
		}
		//allocated
		max_size = capacity;
	}

	/// @brief Returns copy of list
	ll* copyList(ll* node) const {
		if (!node) return nullptr;
		ll* copy = nullptr;
		try {
			copy = new ll{ node->key, node->value };
			copy->next = copyList(node->next);
		}
		catch (const std::bad_alloc& e) {
			delete copy;
			throw;//to delete copies lower in the list
		}
		return copy;
	}

	/// @brief Returns copy of data of currrent object
	ll** copyData() const {
		ll** copy = new ll * [max_size];//bad alloc to catch later
		for (size_t i = 0; i < max_size; i++) {
			if (arr[i])//there is a list
			{
				try {
					copy[i] = copyList(arr[i]);
				}
				catch (const std::bad_alloc& e)
				{
					for (size_t g = 0; g <= i; g++) {//failed, delete everything
						delete copy[g];
					}
					delete copy;
					throw;
				}
			}
			else {
				copy[i] = nullptr;
			}
		}
		return copy;
	}
	/// @brief Allocates memory and makes full copy of other obj
	void tryCopyOther(const Unordered_map<K, T>& other)
	{
		allocateMemory(other.max_size);
		if (max_size == other.max_size) {//we will try to copy everything as it is
			try {
				arr = other.copyData();
				size = other.size;
				return;
			}
			catch (...) {//we couldnt
				delete arr;
				throw;
			}
		}
	
	}



public:
	Unordered_map(const size_t capacity) {
		allocateMemory(capacity);
		for (size_t i = 0; i < max_size; i++) {
			arr[i] = nullptr;
		}
	}
	Unordered_map() :Unordered_map(min_size) {}

	Unordered_map(const Unordered_map<K, T>& other)
	{
		tryCopyOther(other);
	}
	Unordered_map(Unordered_map<K, T>&& other) noexcept
	{
		arr = other.arr;
		other.arr = nullptr;
		max_size = other.max_size;
		other.max_size = 0;
		size = other.size;
		other.size = 0;
	}
	Unordered_map& operator=(const Unordered_map& other) {
		if (&other != this) {
			clear();
			tryCopyOther(other);
		}
		return *this;
	}
	Unordered_map& operator=(Unordered_map&& other) noexcept {
		if (&other != this) {
			clear();
			arr = other.arr;
			other.arr = nullptr;
			max_size = other.max_size;
			other.max_size = 0;
			size = other.size;
			other.size = 0;
		}
		return *this;
	}

	/// @brief Adds element. Best scenario time complexity is O(1)
	void insert(const K& key, const T& value) {
		if (max_size == 0) allocateMemory(min_size);//struct has been erased or not properly made
		size_t h = hash<K>{}(key) % max_size;
		if (!arr[h]) {//its new element
			ll* el = new ll{ key,value };//if error is thrown, no changes will be made
			arr[h] = el;
		}
		else { //there are other el with the same hash - add in the linked list unless it already exists
			ll* el = arr[h];
			if (arr[h]->key == key) return;
			while (el->next) {
				if (el->key == key) return;//we have it added already
				el = el->next;
			}
			ll* newItem = new ll{ key,value }; // if error is thrown, no changes will be made
			el->next = newItem;
		}
		++size;
	}
	/// @brief Removes element if found . Best scenario time complexity is O(1)
	void erase(const K& key) {
		if (size == 0) return;
		int h = hash<K>{}(key) % max_size;
		if (!arr[h] || size == 0) return;

		if (arr[h]->key == key) {//its first el
			ll* el = arr[h]->next;//save pointer to the next
			delete arr[h];//remove the item
			arr[h] = el;//set next as first
		}
		else {
			ll* el = arr[h]->next;
			while (el->next && el->next->key != key) {
				el = el->next;
			}
			if (!el->next) return; //not found
			//else el->next is the searched
			ll* toDel = el->next;
			el->next = toDel->next;
			delete toDel;
		}
		--size;
	}

	/// @brief Returns pointer to the element that contains the key and value (and next element with the same hash)
	ll* find(const K& key) {
		if (size == 0) return nullptr;
		size_t h = hash<K>{}(key) % max_size;
		if (!arr[h]) return nullptr;
		ll* el = arr[h];
		while (el) {
			if (el->key == key) return el;
			el = el->next;
		}
		return nullptr;
	}
	/// @brief Returns true if element is found
	bool contains(const K& key)
	{
		return find(key) != nullptr;
	}
	/// @brief returns the count of different elements in the structure
	size_t get_size() const
	{
		return size;
	}

	bool empty() const
	{
		return size == 0;
	}
	size_t get_bucket_size() const
	{
		return max_size;
	}

	/// @brief Deletes all elements but keeps bucket allocated.
	void clear() noexcept {
		for (size_t i = 0; i < max_size; i++) {
			if (arr[i]) {//list found
				clearList(arr[i]);
				arr[i] = nullptr;
			}
		}
		size = 0;
	}

	~Unordered_map() noexcept
	{
		clear();
		delete arr;
		max_size = 0;
	}

	class UMIterator
	{
	private:
		UMIterator(size_t bucketInd, ll* listPtr, Unordered_map const& obj)
			: bucketInd(bucketInd), listPtr(listPtr), obj(obj) {}
		/// @brief Object that we are working with
		Unordered_map const& obj;
		/// @brief Keeps track of our place in arr
		size_t bucketInd = 0;
		/// @brief Shows where we are in arr[bucketInd] list
		ll* listPtr = nullptr;

	public:
		friend class Unordered_map;

		/// @brief Gets next element in the map. Erasing element that is pointed by the iterator will make it invalid!
		UMIterator& operator++()
		{
			if (!listPtr || !listPtr->next)
			{
				for (size_t i = bucketInd + 1; i < obj.max_size; i++)
				{
					if (obj.arr[i])
					{
						bucketInd = i;
						listPtr = obj.arr[i];
						return *this;
					}
				}
				bucketInd = obj.max_size;
				listPtr = nullptr;
				return *this;
			}
			else
			{
				listPtr = listPtr->next;
				return *this;
			}
		}
		ll* operator*() const
		{
			return listPtr;
		}
		bool operator==(const UMIterator& other) const
		{
			return bucketInd == other.bucketInd && listPtr == other.listPtr;
		}
		bool operator!=(const UMIterator& other) const
		{
			return !(*this == other);
		}
	};

	UMIterator begin()
	{
		for (size_t i = 0; i < max_size; i++)
		{
			if (arr[i])
			{
				return UMIterator(i, arr[i], *this);
			}
		}
		return end();
	}
	UMIterator end()
	{
		return UMIterator(max_size, nullptr, *this);
	}

};

