#include "Player.h"
#include "Deck.h"

class Game
{
private:
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

public:
    Game(); // add cards for players & first card
            // Game(unsigned short startingHand); //generate startingHands

    Card generateCard();
    bool nextTurn();
    void printGame();
    void printCurentCard();
    bool getPlayerRound() const;
};
