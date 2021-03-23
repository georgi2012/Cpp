#pragma once
#include "Cards.h"


const unsigned short MAX_CARDS=10;

class Player{

    private :
        Card hand[MAX_CARDS];
        unsigned short curNumberOfCards;

    public:
        Player();
        Player(unsigned short startingHand ,Card* cards);

        void drawCard(Card newCard);
        bool playCard(unsigned short cardToPlay ,Card lastCard);
        void printHand();
        //void moveCards();
        bool isWinner();
        bool canDraw();
        int getHandSize() const;
        Card removeCard(short index);
        

    private:
        bool isValidCard(const unsigned short cardToPlay ,Card lastCard) const;
       // Card removeCard(short index);
        

};
