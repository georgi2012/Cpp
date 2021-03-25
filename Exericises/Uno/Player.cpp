#include "Player.h"
#include <iostream>
using std::cout;

Player::Player()
{
    curNumberOfCards = 0;
}

Player::Player(unsigned short startingHand, Card *cards)
{
    //if(startingHand is valid? )
    curNumberOfCards = startingHand;
    for (int i = 0; i < startingHand; ++i)
    {
        hand[i].clr = cards[i].clr;
        hand[i].number = cards[i].number;
    }
}

bool Player::canDraw()
{
    return (curNumberOfCards < MAX_CARDS);
}

void Player::drawCard(Card newCard)
{
    if (canDraw())
    {
        hand[curNumberOfCards].clr = newCard.clr;
        hand[curNumberOfCards++].number = newCard.number; //DRY !!!
        return;
    }
    else{//discard first and draw
         removeCard(0);
         hand[curNumberOfCards].clr = newCard.clr;
         hand[curNumberOfCards++].number = newCard.number; //DRY !!!
         return;
    }
}

Card Player::removeCard(short index)
{
    Card removedCard;
    
    if (index < curNumberOfCards && index >= 0)
    {
        removedCard.number = hand[index].number;
        removedCard.clr = hand[index].clr;

        for (int i = index + 1; i < curNumberOfCards; ++i)
        {
            hand[i - 1].clr = hand[i].clr;
            hand[i - 1].number = hand[i].number;
        }
        curNumberOfCards--;
        hand[curNumberOfCards].clr=unknown;
        hand[curNumberOfCards].number= UNKNOWN_NUM;
        return removedCard;
    }
    //else
    removedCard.clr = unknown;
    removedCard.number = UNKNOWN_NUM;
    throw - 1;
    return removedCard;
    //throw error?
}

bool Player::isWinner()
{
    return (curNumberOfCards == 0);
}

int Player::getHandSize() const
{
    return curNumberOfCards;
}

void Player::printHand(const int currentChoice=-1)
{
    cout << "Your current Hand :\n";
    for (int i = 0; i < curNumberOfCards; ++i)
    {
        cout << "\n"
             << i << ". ";
        switch (hand[i].clr)
        {
        case red:
            cout << " Red ";
            break;
        case blue:
            cout << " Blue ";
            break;
        case green:
            cout << " Green ";
            break;
        case yellow:
            cout << " Yellow ";
            break;
        default:
            cout << " Unknown ("<<hand[i].clr<<") ";
            break;
        } //switch
        cout << " [" << hand[i].number << "] ";
        if(currentChoice==i)
        { 
            cout << " <--[ Your current choice ]";
        }
    } //for
}

bool Player::isValidCard(const unsigned short cardToPlay ,Card lastCard) const
{
   return (cardToPlay==curNumberOfCards ||  hand[cardToPlay].clr==lastCard.clr || hand[cardToPlay].number==lastCard.number);
}//cardToPlay==curNumberOfCards  means drawing a card

bool Player::playCard(unsigned short cardToPlay ,Card lastCard){

    //cout<<cardToPlay<<isValidCard(cardToPlay,lastCard)<<" clr "<<hand[cardToPlay].clr <<" num "<<hand[cardToPlay].number<<std::endl;
    //cout<<"cur card: "<<lastCard.clr<<" num: "<<lastCard.number<<std::endl;
      return isValidCard(cardToPlay,lastCard); // not much sense but it's more readable that way...
}

const Card* Player::getHand() const{
   return hand;
 }


