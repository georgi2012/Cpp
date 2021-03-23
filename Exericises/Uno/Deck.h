#pragma once
#include "Cards.h"

class Deck{
    private :
        unsigned cardsLeft;
        Card deck[36];

        void shuffleNewDeck(Card* plrOneHand=nullptr,Card* plrTwoHand=nullptr);
        bool isInHand(Card * &Hand, unsigned short num , unsigned short clrIndex) const;
        void findPlaceInDeck(unsigned short num, unsigned short clrIndex);

    public:
        Deck();
        Card drawCard();

};