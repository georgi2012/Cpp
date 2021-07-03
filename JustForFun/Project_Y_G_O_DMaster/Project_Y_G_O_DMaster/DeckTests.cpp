#define CATCH_CONFIG_MAIN  
#include "Deck.h"
#include "catch.hpp"


TEST_CASE("Testing deck creeation and cards arrangement with 20 cards") {
	std::string fileName = "DeckList1.txt";
	Deck deck(fileName, 25);
	deck.printDeck();
}