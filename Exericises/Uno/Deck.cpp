#include "Deck.h"
#include <cstdlib>
//#include <ctime>

Deck::Deck()
{
    //srand(time(NULL));
    shuffleNewDeck(); //will set cards to 36
}

void Deck::findPlaceInDeck(unsigned short num, unsigned short clrIndex)
{
    //ewCard.number = rand() % 9 + 1;
    // newCard.clr = static_cast<COLOR>(rand() % 4 + 1);
    unsigned place = rand() % 36; //0-35
    bool isFoundEmpty = false;
    bool isIncreasing = true;
    int br = place;
    while (!isFoundEmpty && br >= 0)
    {
        if (br > 35)
        {
            br = place;
            isIncreasing = false;
        }
        if (deck[br].number == 11) //not taken
        {
            isFoundEmpty = true;
            deck[br].number = num;
            deck[br].clr = static_cast<COLOR>(clrIndex);
            break;
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
        throw -1;
    }
}

bool Deck::isInHand(const Card *&Hand, unsigned short num, unsigned short clrIndex) const
{

    int i = 0;
    while (i < 10 && Hand[i].number != 11) //while there are cards and we havent found the last card in the hand
    {
        if (Hand[i].number == num && Hand[i].clr == static_cast<COLOR>(clrIndex))
        {
            return true;
        }
        i++;
    }
    return false;
}

void Deck::shuffleNewDeck(const Card *plrOneHand ,const Card *plrTwoHand )
{
    //srand(time(NULL));
    if (plrOneHand == nullptr) //it's called from constructor
    {
        for (int i = 1; i <= 9; i++) //numbers
        {
            for (int j = 1; j <= 4; j++) //colors
            {
                findPlaceInDeck(i, j);
            }
        }
        cardsLeft = 36;
        return;
    }
    //cards are supposed to be at 0 now
    for (int i = 0; i < 9; i++) //numbers
    {
        for (int j = 0; j < 4; j++) //colors
        {
            if (!isInHand(plrOneHand, i, j) && !isInHand(plrTwoHand, i, j)) // ! IT WILL LEFT HOLES IN THE DECK , TAKE CARE OF THEM LATER !
            {
                findPlaceInDeck(i, j);
                cardsLeft++;
            }
        }
    }
    return;
}

Card Deck::drawCard()
{ //we should have already checked if there are any cards left!
    cardsLeft--;
    int cardIndex=35; //there can be 'holes' in our deck.
    while (deck[cardIndex].number == 11) //invalid card, continue
    {
        cardIndex--;
    }
    Card cardToDraw=deck[cardIndex];
    deck[cardIndex].clr=unknown;
    deck[cardIndex].number=11;
    return cardToDraw;
}

unsigned Deck::getCardsLeft() const
{
    return cardsLeft;
}