#pragma once
#include "Cards.h"

class Deck{
    private :
        unsigned cardsLeft;
        Card deck[46];

        bool isInHand(const Card * &Hand, unsigned short num , unsigned short clrIndex) const;

    public:
        Deck();
        Card drawCard(); //takes the next card 
        unsigned getCardsLeft() const;
        void shuffleNewDeck(const Card* plrOneHand=nullptr,const Card* plrTwoHand=nullptr);
        void findPlaceInDeck(unsigned short num, unsigned short clrIndex);

};