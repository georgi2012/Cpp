#define CATCH_CONFIG_MAIN  
#include "CardsDatabase.h"
#include "catch.hpp"


TEST_CASE("Reading file and loading info")
{
	//std::fstream file("DeckList1.txt", std::ios::in);
	std::string fileName = "DeckList1.txt";
	CardsDatabase dataB;
	dataB.loadDatabase(fileName);
	dataB.printCards();
}