#include "Deck.h"
#include <time.h> 
#include <stdlib.h>
using std::cout;
void Deck::generateDeck()
{
	unsigned dublicates = curDeckSize / dataB.getAllCardsNum();
	short lefts = curDeckSize % dataB.getAllCardsNum();
	if (dublicates > 0) {
		for (unsigned i = 0; i < dataB.getAllCardsNum(); i++) {
			for (unsigned j = 0; j < dublicates; j++) {
				cards[findPlaceInDeck()] = dataB[i];
			}
		}
	}
	for (unsigned i = 0; i < lefts; i++) {//first cards will have more copies
		cards[findPlaceInDeck()] = dataB[i];
	}
}

unsigned short Deck::findPlaceInDeck()
{
	unsigned place = std::rand() % curDeckSize; //0-(curdeckSize-1)
	bool isFoundEmpty = false;
	bool isIncreasing = true;
	int br = place;
	while (!isFoundEmpty && br >= 0)
	{
		if (br > curDeckSize - 1)
		{
			br = place;
			isIncreasing = false;
		}
		if (cards[br] == nullptr) //not taken
		{
			return br;
		}
		if (isIncreasing)
		{
			br++;
		}
		else
		{
			br--;
		}
	} //while
	if (!isFoundEmpty)
	{
		throw - 1;
	}
}

Deck::Deck(std::string filePath, unsigned deckSize) :curDeckSize(deckSize)
{
	try {
		dataB.loadDatabase(filePath);
	}
	catch (...) {
		cout << "Loading database filed with " << filePath<<std::endl;
	}
	curDeckSize = deckSize;
	cards.resize(deckSize);
	for (unsigned i = 0; i < deckSize; i++) {
		cards[i] = nullptr;
	}
	srand(time(NULL));
	generateDeck();
}

const Card* Deck::draw()
{
	if (curDeckSize == 0) {
		throw - 1;
	}
	const Card* lastCard = cards[--curDeckSize];//take last
	cards.pop_back();//remove last
	return lastCard;
}

void Deck::printDeck()
{
	for (int i = 0; i < cards.size(); i++) {
		cout <<i+1<<"."<< (*cards[i]).getCardName()<<std::endl;
	}
}
