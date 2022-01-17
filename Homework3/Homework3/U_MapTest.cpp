#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include "catch.hpp"
#include "Unordered_Map.h"

using std::string;


SCENARIO("Testing Unordered_Map with key string and size_t value")
{
	const unsigned min_size = 1000;
	GIVEN("Searching in empty u_map")
	{
		Unordered_map<string, size_t> umap;
		REQUIRE(umap.empty());
		REQUIRE(umap.get_bucket_size() == min_size);
		REQUIRE(umap.get_size() == 0);
		REQUIRE(umap.contains("") == false);
		REQUIRE(umap.find("") == nullptr);
		for (auto el : umap) {//el is pointer
			REQUIRE(false);//should not get here at all
		}
	}
	GIVEN("Testing with string/size_t u_map")
	{
		Unordered_map<string, size_t> umap;
		WHEN("Try inserting unique elements")
		{
			umap.insert("First", 1);
			umap.insert("sec", 2);
			umap.insert("third", 3);
			umap.insert("some", -1);
			REQUIRE(umap.get_size() == 4);
			THEN("Searching for the elements")
			{
				REQUIRE(umap.contains("First"));
				REQUIRE(umap.contains("sec"));
				REQUIRE(umap.contains("third"));
				REQUIRE(umap.contains("some"));

			}
			THEN("Accessing elements")
			{
				auto el = umap.find("First");
				REQUIRE(el->key == "First");
				REQUIRE(el->value == 1);
				el = umap.find("some");
				REQUIRE(el->key == "some");
				REQUIRE(el->value == -1);
				el = umap.find("missing");
				REQUIRE(el == nullptr);
			}
			THEN("Iterate through them")
			{
				bool found[4] = { false,false,false,false };
				for (auto el : umap)
				{
					if (el->key == "First" && !found[0])
					{
						found[0] = true;
					}
					else if (el->key == "sec" && !found[1])
					{
						found[1] = true;
					}
					else if (el->key == "third" && !found[2])
					{
						found[2] = true;
					}
					else if (el->key == "some" && !found[3])
					{
						found[3] = true;
					}
				}
				for (bool el : found) {
					REQUIRE(el == true);
				}
			}
			THEN("Remove some of them") {
				umap.erase("First");
				REQUIRE(umap.contains("First") == false);
				REQUIRE(umap.get_size() == 3);
				umap.erase("third");
				REQUIRE(umap.contains("third") == false);
				REQUIRE(umap.get_size() == 2);
				umap.erase("invalid");
				REQUIRE(umap.get_size() == 2);
			}
			THEN("Testing Reinsert of same element")
			{
				umap.insert("third", 3);
				REQUIRE(umap.get_size() == 4);
				REQUIRE(umap.contains("third"));
				REQUIRE(umap.find("third")->value == 3);
			}
			THEN("Testing Clear")
			{
				umap.clear();
				REQUIRE(umap.empty());
				REQUIRE(umap.contains("First") == false);
				REQUIRE(umap.contains("third") == false);
				REQUIRE(umap.contains("sec") == false);
				REQUIRE(umap.contains("some") == false);
			}

		}

	}
	GIVEN("Testing assigning custom size for bucket")
	{
		const unsigned max_limit_size = 100'019;
		WHEN("Test for 10'000") {
			Unordered_map<bool, bool> umap(10'000);
			THEN("Check if allocated 10'000") {
				REQUIRE(umap.get_bucket_size() == 10'000);
			}
		}
		WHEN("Check for more than the limit size (allocation is possible to fail in that test)")
		{
			Unordered_map<bool, bool> umap(100'100);
			THEN("Check if allocated the maximum") {
				REQUIRE(umap.get_bucket_size() == 100'019);
			}


		}
	}
	GIVEN("Testing copy constructor")
	{
		Unordered_map<string, size_t> umap;
		umap.insert("1", 1);
		umap.insert("2", 2);
		umap.insert("3", 3);
		WHEN("Building the copy u_map")
		{
			Unordered_map<string, size_t> copy(umap);
			THEN("Check if set correctly")
			{
				REQUIRE(copy.get_size() == 3);
				for (auto el : umap) {
					auto found = copy.find(el->key);
					REQUIRE(found != nullptr);
					REQUIRE(found->value == el->value);
				}
			}
		}
	}
	GIVEN("Testing move constructor")
	{
		Unordered_map<string, size_t> umap;
		umap.insert("1", 1);
		umap.insert("2", 2);
		umap.insert("3", 3);
		WHEN("Building the copy u_map")
		{
			Unordered_map<string, size_t> helper(umap);
			Unordered_map<string, size_t> copy(std::move(umap));
			THEN("Check if set correctly")
			{
				REQUIRE(copy.get_size() == 3);
				REQUIRE(umap.get_size() == 0);

				for (auto el : helper) {
					auto found = copy.find(el->key);
					REQUIRE(umap.contains(el->key) == false);
					REQUIRE(found != nullptr);
					REQUIRE(found->value == el->value);
				}
			}
		}
	}
	GIVEN("Testing operator= ")
	{
		Unordered_map<string, size_t> umap;
		umap.insert("1", 1);
		umap.insert("2", 2);
		umap.insert("3", 3);
		WHEN("Building the copy u_map")
		{
			Unordered_map<string, size_t> copy;
			copy = umap;
			THEN("Check if set correctly")
			{
				REQUIRE(copy.get_size() == 3);
				for (auto el : umap) {
					auto found = copy.find(el->key);
					REQUIRE(found != nullptr);
					REQUIRE(found->value == el->value);
				}
			}
		}

	}
}


