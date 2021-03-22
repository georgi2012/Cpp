#include "Player.h"


class Game{
    private:
         //int numberOfPlayers; //=2
         //bool cardsPile[4][9]; //unique cards to be drawn 
         Player players[2];
         Card currentCard;
         bool isFPlRound; //is first player's turn
         
    
    public :
        Game(); // add cards for players & first card
       // Game(unsigned short startingHand); //generate startingHands
        
        Card generateCard();
        bool nextTurn();
        void printGame(); 
        void printCurentCard();
        bool getPlayerRound() const;


};


/*


 Current card :  red  2  //current Idea 

   0. /red 3 /
   1. /yellow 4/



   Updated idea :




*/