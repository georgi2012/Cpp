#include "Deck.h"
#include <cstdlib>
//#include <ctime>

Deck::Deck()
{
    //srand(time(NULL));
    shuffleNewDeck(); //will set cards to 46
}

void Deck::findPlaceInDeck(unsigned short num, unsigned short clrIndex)
{
    //ewCard.number = rand() % 9 + 1;
    // newCard.clr = static_cast<COLOR>(rand() % 4 + 1);
    unsigned place = rand() % 46; //0-45
    bool isFoundEmpty = false;
    bool isIncreasing = true;
    int br = place;
    while (!isFoundEmpty && br >= 0)
    {
        if (br > 45)
        {
            br = place;
            isIncreasing = false;
        }
        if (deck[br].number == UNKNOWN_NUM) //not taken
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
    while (i < 10 && Hand[i].number != UNKNOWN_NUM) //while there are cards and we havent found the last card in the hand
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
        for (int i = 1; i <= CHANGEDIR_NUMBER; i++) //numbers
        {
            for (int j = 1; j <= 4; j++) //colors
            {
                findPlaceInDeck(i, j);
            }
        }
        findPlaceInDeck(DRAW4_NUMBER, 1); //as +4 is quite powerful , I will add it just twice
        findPlaceInDeck(DRAW4_NUMBER, 1);
        cardsLeft = 46;
        return;
    }
    //cards are supposed to be at 0 now
    for (int i = 1; i <= CHANGEDIR_NUMBER; i++) //numbers
    {
        for (int j = 1; j <= 4; j++) //colors
        {
            if (!isInHand(plrOneHand, i, j) && !isInHand(plrTwoHand, i, j)) // ! IT WILL LEFT HOLES IN THE DECK , TAKE CARE OF THEM LATER !
            {
                findPlaceInDeck(i, j);
                cardsLeft++;
            }
        }
    }
    for (int i = 0; i < 2; i++) { //+4 
        if (!isInHand(plrOneHand, DRAW4_NUMBER, 1) && !isInHand(plrTwoHand, DRAW4_NUMBER, 1)) // ! IT WILL LEFT HOLES IN THE DECK , TAKE CARE OF THEM LATER !
        {
            findPlaceInDeck(DRAW4_NUMBER, 1);
            cardsLeft++;
        }
    }
    return;
}

Card Deck::drawCard()
{ //we should have already checked if there are any cards left!
    cardsLeft--;
    int cardIndex=45; //there can be 'holes' in our deck.
    while (deck[cardIndex].number == UNKNOWN_NUM) //invalid card, continue
    {
        cardIndex--;
    }
    Card cardToDraw=deck[cardIndex];
    deck[cardIndex].clr=unknown;
    deck[cardIndex].number= UNKNOWN_NUM;
    return cardToDraw;
}

unsigned Deck::getCardsLeft() const
{
    return cardsLeft;
}