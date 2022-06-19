#define CATCH_CONFIG_MAIN  
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <unordered_set>
//
#include "catch.hpp"
#include "../RBvsSkipList/RedBlackTree.h"
//#include "DelLatercpp.cpp"

SCENARIO("Testing RBTree class insertion") {
	srand(time(NULL));
	GIVEN("Creating default object") {
		RBTree tree;
		WHEN("Insert 3 elements") {
			tree.insert(1);
			tree.insert(3);
			tree.insert(2);
			THEN("Test finding the elements") {
				REQUIRE(tree.exists(1));
				REQUIRE(tree.exists(2));
				REQUIRE(tree.exists(3));
				REQUIRE(tree.exists(4) == false);
			}
			THEN("Test for getSize") {
				REQUIRE(tree.getSize() == 3);
			}//then
		}//when
		WHEN("Insert 1000 random elements") {

			int values[1000];
			for (int i = 0; i < 1000; i++) {
				values[i] = rand() % 100000;
				if (i % 2) values[i] *= -1;
				tree.insert(values[i]);
			}
			THEN("Test finding the elements") {
				for (int i = 0; i < 1000; i++)
					REQUIRE(tree.exists(values[i]));

			}
			THEN("Test for getSize") {
				REQUIRE(tree.getSize() == 1000);
			}//then
		}//when
	}//given
}//scen

SCENARIO("Testing RBTree class deletion") {
	srand(time(NULL));
	GIVEN("Creating default object") {
		RBTree tree;
		WHEN("Insert 3 elements") {
			tree.insert(1);
			tree.insert(3);
			tree.insert(2);
			THEN("Try removing them") {
				REQUIRE(tree.exists(2));
				tree.remove(2);
				REQUIRE(!tree.exists(2));
				REQUIRE(tree.getSize() == 2);
				REQUIRE(tree.exists(1));
				tree.remove(1);
				REQUIRE(!tree.exists(1));
				REQUIRE(tree.getSize() == 1);
				REQUIRE(tree.exists(3));
				tree.remove(3);
				REQUIRE(!tree.exists(3));
				REQUIRE(tree.getSize() == 0);
				/*tree.deleteByVal(2);
				tree.deleteByVal(1);
				tree.deleteByVal(3);*/
			}
		}//when
		WHEN("Insert 1000 random elements") {
			int values[1000];
			std::unordered_set<int> set;
			for (int i = 0; i < 1000; i++) {
				do {
					values[i] = rand() % 100000;
				} while (set.count(values[i]));//create unique elements
				if (i % 2) values[i] *= -1;
				set.insert(values[i]);
				tree.insert(values[i]);
				//std::cout << values[i] << " ";
				//tree.insert(i);
			}
			THEN("Test removing half of them") {
				for (int i = 0; i < 500; i++)
					tree.remove(values[i]);
					//tree.remove(i);
				//tree.deleteByVal(values[i]);
				for (int i = 0; i < 500; i++) {
					REQUIRE(!tree.exists(values[i]));
					//REQUIRE(!tree.exists(i));
				}
				for (int i = 500; i < 1000; i++) {
					REQUIRE(tree.exists(values[i]));
					//REQUIRE(tree.exists(i));
				}
				REQUIRE(tree.getSize() == 500);
			}

		}//when
	}//given
}//scen

SCENARIO("Test RBTree class operators and constructors")
{
	GIVEN("Test copy constr and copy operator=") {
		RBTree tree;
		WHEN("Fill the default tree with 1000 random values") {
			int values[1000];
			for (int i = 0; i < 1000; i++) {
				values[i] = rand() % 10000;
				if (i % 2) values[i] *= -1;
				tree.insert(values[i]);
			}
			THEN("Make a copy with constr") {
				RBTree copyTree = tree;
				AND_THEN("Test if copy has the correct values") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(copyTree.exists(values[i]));
				}
			}//then
			THEN("Make a copy with oper=") {
				RBTree copyTree;
				copyTree = tree;
				AND_THEN("Test if copy has the correct values") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(copyTree.exists(values[i]));
				}
			}//then
		}//when
	}//given
	GIVEN("Test move constr and move operator=") {
		RBTree tree;
		WHEN("Fill the default tree with 1000 random values") {
			int values[1000];
			for (int i = 0; i < 1000; i++) {
				values[i] = rand() % 10000;
				if (i % 2) values[i] *= -1;
				tree.insert(values[i]);
			}
			THEN("Move with constr") {
				RBTree movedtree = std::move(tree);
				AND_THEN("Test if old tree is empty") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(!tree.exists(values[i]));
					REQUIRE(tree.getSize() == 0);
				}
				AND_THEN("Test if new tree is moved") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(movedtree.exists(values[i]));
					REQUIRE(movedtree.getSize() == 1000);
				}
			}//then
			THEN("Move with oper=") {
				RBTree movedtree;
				movedtree = std::move(tree);
				AND_THEN("Test if old tree is empty") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(!tree.exists(values[i]));
					REQUIRE(tree.getSize() == 0);
				}
				AND_THEN("Test if new tree is moved") {
					for (int i = 0; i < 1000; i++)
						REQUIRE(movedtree.exists(values[i]));
					REQUIRE(movedtree.getSize() == 1000);
				}
			}//then
		}//when
	}//given

}//scen

