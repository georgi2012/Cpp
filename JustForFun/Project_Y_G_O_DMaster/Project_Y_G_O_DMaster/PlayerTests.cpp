#define CATCH_CONFIG_MAIN  
#include "Player.h"
#include "catch.hpp"



TEST_CASE("Testing hand displaying") {
	std::string fileName = "DeckList1.txt";
	Player pl1(fileName, 25, 4000, 1);
	pl1.displayHand();
}