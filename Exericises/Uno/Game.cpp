#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Game.h"
//#include <conio.h>

using std::cin;
using std::cout;
using std::endl;

Game::Game()
{
    cardsInPile=4*9;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<9;j++)
        {
            cardsPile[i][j]=1; // we can draw that card
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; j++)
        {
            players[i].drawCard(generateCard());
        }
    }
    currentCard = generateCard();
    isFPlRound = true;
}

Card Game::generateCard()
{
    Card newCard;
    if(cardsInPile==0)
    {
        
    }
    //srand(time(NULL));
    newCard.number = rand() % 9 + 1;
    newCard.clr = static_cast<COLOR>(rand() % 4 + 1);
    return newCard;
}

void Game::printCurentCard()
{
    //cout << "\nCurrent card : " << currentCard.clr << "  " << currentCard.clr << endl;
    switch (currentCard.clr)
    {
    case red:
    {
        cout << endl;
        cout << R"(  _____          _  )" << endl;
        cout << R"( |  __ \        | | )" << endl;
        cout << R"( | |__) |___  __| | )" << endl;
        cout << R"( |  _  // _ \/ _` |)" << endl;
        cout << R"( | | \ \  __/ (_| | )" << endl;
        cout << R"( |_|  \_\___|\__,_| )" << endl;
        break;
    }
    case blue:
    {
        cout << endl;
        cout << "   ____  _   " << endl;
        cout << R"(  |  _ \| |  )" << endl;
        cout << R"(  | |_) | |_ ___  ___  )" << endl;
        cout << R"(  |  _ <| | | | |/ _ \ )" << endl;
        cout << R"(  | |_) | | |_| |  __/ )" << endl;
        cout << R"(  |____/|_|\__,_|\___| )" << endl
             << endl;
        break;
    }
    case yellow:
    {
        cout << R"(              _ _               )" << endl;
        cout << R"(             | | |              )" << endl;
        cout << R"(   _   _  ___| | | _____      __  )" << endl;
        cout << R"(  | | | |/ _ \ | |/ _ \ \ /\ / /)" << endl;
        cout << R"(  | |_| |  __/ | | (_) \ V  V / )" << endl;
        cout << R"(   \__, |\___|_|_|\___/ \_/\_/ )" << endl;
        cout << R"(   |___/  )" << endl;

        break;
    }
    case green:
    {
        cout << R"(   __ _ _ __ ___  ___ _ __   )" << endl;
        cout << R"(  / _` | '__/ _ \/ _ \ '_ \  )" << endl;
        cout << R"( | (_| | | |  __/  __/ | | | )" << endl;
        cout << R"(  \__, |_|  \___|\___|_| |_|)" << endl;
        cout << R"(   __/ |   )" << endl;
        cout << R"(  |___/    )" << endl;
        cout << "\n\n";
        break;
    }
    default:
        cout << "no such color";
        break;
    }

    cout << currentCard.number << endl;
    return;
}

void Game::printGame()
{
    system("cls");
    printCurentCard();
    cout << "Player " << isFPlRound+1 << " 's turn \n";
    players[isFPlRound].printHand();
    cout << "\n" << players[isFPlRound].getHandSize() << ". Draw a card.";
    cout << "\n ";
}

void fixCin()
{
    cin.clear();
    cin.ignore(100, '\n');
}

bool Game::nextTurn()
{
    printGame();
    int playerChoice=-1;
    Card removedCard;

    do
    { //find a valid card and play it
        cout << "\nEnter your next card's index: ";
        cout<<playerChoice<<endl;
        if (!cin)
        {
            fixCin();
        }
        cin >> playerChoice;

    } while (!cin || !(playerChoice >= 0 && playerChoice <= 10 && players[isFPlRound].playCard(playerChoice, currentCard)));

    if (playerChoice == players[isFPlRound].getHandSize()) //he has choisen to draw a card
    {
        players[isFPlRound].drawCard(generateCard()); //draw a card or discard first + draw
    }
    else
    {                                                               //play a card
        removedCard = players[isFPlRound].removeCard(playerChoice); //remove the card from hand
        currentCard.clr = removedCard.clr;                          //put on table new card
        currentCard.number = removedCard.number;                    //put on table new card
    }

    if (players[isFPlRound].isWinner())
    {
        return true;
    }
    isFPlRound = !isFPlRound; //player change
    return false;
}

bool Game::getPlayerRound() const
{
    return isFPlRound;
}

int main()
{
    srand(time(NULL));
    Game gameSession;               //players declared . Cards drawn. First card put on table.
    while (!gameSession.nextTurn()) //while there is no winner
    {
        // :)
    }
    cout << " And the big winner is Player " << gameSession.getPlayerRound()+1 << " !\n";

    return 0;
}