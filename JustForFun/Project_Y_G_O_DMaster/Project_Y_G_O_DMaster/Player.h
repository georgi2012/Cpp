#pragma once
#include "Deck.h"
#include <iomanip> //setw
#include <conio.h>//getch

#define MAX_HAND_SIZE 6
#define ARROW_START_POS 7 //13's middle
//operator[]?
class Player : protected Deck{
protected:
	std::vector<const Card*> hand;
	bool isPlayerOne;
	int lifePoints;
	short attemptCardIndex = -1;

public:
	Player(std::string filePath, unsigned deckSize, int LifePoints, bool isPlayerOne);
	int getLP() const;
	bool isFirstPlayer() const;
	void displayHand();
	const Card* attemptCardPlay(short index); //returns the card in that index after plr choose it. If is played-will resolve.
	void resolveCardPlay(short discardIndex=-1);//works as discard as well
	
};
/*The limit is Six, but this is only enforced at the end of your turn;
during any period after or before, you are allowed any number of cards in 
your hand. At the end of your turn, you are required to discard cards from 
your hand until you have six cards in your hand.*/