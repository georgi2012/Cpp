#include "Player.h"
#include "Deck.h"

#define ENTER_SYMBOW '\r'

class Game
{
//private:
public:
    //int numberOfPlayers; //=2
    //bool cardsPile[4][9]; //unique cards to be drawn
    //unsigned cardsInPile;
    Player players[2];
    Card currentCard;
    Deck cardsPile;

    bool isScndRound; //is first player's turn

    void shuffleNewPile(Card *frstPlrHand, Card *scndPlrHand); //called when pile is empty
    void printHelperNum(std::string *&ptr) const;
    void printHelperClr(std::string *&ptr) const;
    void printColorPicker(short choice) const;
    COLOR specialCard_Draw4();
    void specialCard_ChangeDir();
    COLOR specialCard_ChangeClr();

public:
    Game(); // add cards for players & first card
            // Game(unsigned short startingHand); //generate startingHands

    Card generateCard();
    bool nextTurn();
    void printGame(const int currentChoice,bool isSpecialCard);
    void printCurentCard();
    bool getPlayerRound() const;
};
