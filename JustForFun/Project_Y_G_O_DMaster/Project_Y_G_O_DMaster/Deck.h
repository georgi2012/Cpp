#pragma once
#include "Card.h"
#include "CardsDatabase.h"

#define MAX_DECK_SIZE 30;

class Deck {
private:
	CardsDatabase dataB;
	std::vector<const Card*> cards;
	unsigned curDeckSize;

	unsigned short findPlaceInDeck();
	void generateDeck();
public:
	Deck(std::string filePath,unsigned deckSize);
	const Card* draw();//throw exception if no cards are left in deck?
	void printDeck();
};