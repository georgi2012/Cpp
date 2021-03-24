#include <iostream>
//#include <cstdlib>
#include <windows.h>
#include <ctime>

#include "Game.h"
//#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Game::printHelperNum(string*& ptr) const
{
	// string *ptr;
	switch (currentCard.number)
	{
	case 1:
	{
		ptr=new string [6]{ R"( __ )",
							R"(/_ |)",
							R"( | |)",
							R"( | |)",
							R"( | |)",
							R"( |_|)" };
		//ptr = number;
		return;// ptr;
	}
	case 2:
	{
		ptr = new string[6]{
			R"( ___  )",
			R"(|__ \ )",
			R"(   ) |)",
			R"(  / / )",
			R"( / /_ )",
			R"(|____|)" };
		//ptr = number;
		return;// ptr;
	}
	case 3:
	{
		ptr = new string[6]{
			R"(  ____  )",
			R"( |___ \ )",
			R"(   __) |)",
			R"(  |__ < )",
			R"(  ___) ))",
			R"( |____/ )" };
		//ptr = number;
		return;// ptr;
	}
	case 4:
	{
		ptr = new string[6]{
			R"(  _  _   )",
			R"( | || |  )",
			R"( | || |_ )",
			R"( |__   _|)",
			R"(    | |  )",
			R"(    |_|  )" };
		//ptr = number;
		return;// ptr;
	}
	case 5:
	{
		ptr = new string[6]{
			R"(  _____ )",
			R"( | ___| )",
			R"( | |__  )",
			R"( |___ \ )",
			R"(  ___) |)",
			R"( |____/)" };
		//ptr = number;
		return;// ptr;
	}
	case 6:
	{
		ptr = new string[6]{
			R"(    __  )",
			R"(   / /  )",
			R"(  / /_  )",
			R"( | '_ \ )",
			R"( | (_) |)",
			R"(  \___/ )" };
		//ptr = number;
		return;// ptr;
	}

	case 7:
	{
		ptr = new string[6]{
			R"(  ______ )",
			R"( |____  |)",
			R"(     / / )",
			R"(    / /  )",
			R"(   / /   )",
			R"(  /_/    )" };
		//ptr = number;
		return;// ptr;
	}

	case 8:
	{
		ptr = new string[6]{
			R"(   ___  )",
			R"(  / _ \ )",
			R"( | (_) |)",
			R"(  > _ < )",
			R"( | (_) |)",
			R"(  \___/  )" };
		//ptr = number;
		return;// ptr;
	}
	case 9:
	{
		ptr = new string[6]{
			R"(   ___  )",
			R"(  / _ \ )",
			R"( | (_) |)",
			R"(  \__, |)",
			R"(    / / )",
			R"(   /_/  )" };
		//ptr = number;
		return;// ptr;
	}
	default:
		return;// nullptr;
	}
}

void Game::printHelperClr(string*& ptr) const
{
	//string *ptr;

	switch (currentCard.clr)
	{
	case red:
	{
		ptr = new string[6]  {
			R"(  _____          _  )",
			R"( |  __ \        | | )",
			R"( | |__) |___  __| | )",
			R"( |  _  // _ \/ _` | )",
			R"( | | \ \  __/ (_| | )",
			R"( |_|  \_\___|\__,_| )" };
		//ptr = colors;
		return;//ptr;
	}
	case blue:
	{
		ptr = new string[6]{
			R"(   ____  _             )",
			R"(  |  _ \| |            )",
			R"(  | |_) | |_ ___  ___  )",
			R"(  |  _ <| | | | |/ _ \ )",
			R"(  | |_) | | |_| |  __/ )",
			R"(  |____/|_|\__,_|\___| )" };
		//ptr = colors;
		return;// ptr;
	}
	case yellow:
	{
		ptr = new string[6]{
			R"(             | | |              )",
			R"(   _   _  ___| | | _____      __)",
			R"(  | | | |/ _ \ | |/ _ \ \ /\ / /)",
			R"(  | |_| |  __/ | | (_) \ V  V / )",
			R"(   \__, |\___|_|_|\___/ \_/\_/  )",
			R"(   |___/                        )" };

		//ptr = colors;
		return;// ptr;
	}
	case green:
	{
		ptr = new string[6]{
			R"(   __ _ _ __ ___  ___ _ __   )",
			R"(  / _` | '__/ _ \/ _ \ '_ \  )",
			R"( | (_| | | |  __/  __/ | | | )",
			R"(  \__, |_|  \___|\___|_| |_| )",
			R"(   __/ |                     )",
			R"(  |___/                      )" };
		//ptr = colors;
		return;// ptr;
	}
	default:
		return;//nullptr;

	}
}

Game::Game()
{
	//cardsInPile=4*9;
	/*for(int i=0;i<4;i++)
	{
		for(int j=0;j<9;j++)
		{
			cardsPile[i][j]=1; // we can draw that card
		}
	}*/
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			players[i].drawCard(generateCard());
		}
	}
	currentCard = generateCard();
	isScndRound = false;
}

Card Game::generateCard()
{
	Card newCard;
	if (cardsPile.getCardsLeft() == 0)
	{
		cardsPile.shuffleNewDeck(players[0].getHand(), players[1].getHand());
	}
	//cout<<" (left:"<<cardsPile.getCardsLeft()<<") ";
	//srand(time(NULL));
	//newCard.number = rand() % 9 + 1;
	//newCard.clr = static_cast<COLOR>(rand() % 4 + 1);
	return cardsPile.drawCard();
}

void Game::printCurentCard()
{

	string* cardNum;// = printHelperNum(); //not raw
	printHelperNum(cardNum);
	string* cardClr;// = printHelperClr();
	printHelperClr(cardClr);

	//cout << "\nCurrent card : " << currentCard.clr << "  " << currentCard.clr << endl;
	/*switch (currentCard.clr)
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
	}*/
	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << cardClr[i] << " " << cardNum[i] << endl;
	}
	cout << endl;
	//cout << currentCard.number << endl;
	delete[] cardNum;
	delete[] cardClr;
	return;
}

void Game::printGame()
{
	system("cls");
	printCurentCard();
	cout << "Player " << isScndRound + 1 << " 's turn \n";
	players[isScndRound].printHand();
	cout << "\n"
		<< players[isScndRound].getHandSize() << ". Draw a card.";
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
	int playerChoice = -1;
	Card removedCard;

	do
	{ //find a valid card and play it
		cout << "\nEnter your next card's index: ";
		// cout<<playerChoice<<endl;
		if (!cin)
		{
			fixCin();
		}
		cin >> playerChoice;

	} while (!cin || !(playerChoice >= 0 && playerChoice <= 10 && players[isScndRound].playCard(playerChoice, currentCard)));

	if (playerChoice == players[isScndRound].getHandSize()) //he has choisen to draw a card
	{
		players[isScndRound].drawCard(generateCard()); //draw a card or discard first + draw
	}
	else
	{                                                                //play a card
		removedCard = players[isScndRound].removeCard(playerChoice); //remove the card from hand
		currentCard.clr = removedCard.clr;                           //put on table new card
		currentCard.number = removedCard.number;                     //put on table new card
	}

	if (players[isScndRound].isWinner())
	{
		return true;
	}
	isScndRound = !isScndRound; //player change
	return false;
}

bool Game::getPlayerRound() const
{
	return isScndRound;
}

//Test
/*
void print(Game& gameSession)
{
	 int nums[10]={};
   int clrs[5]={};
   Card somecard;
   for(int i=0;i<29;i++)
   {
	 somecard=gameSession.generateCard();
	 cout<<"\n"<<i<<" ";
	 switch (somecard.clr)
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
			cout << " Unknown ";
			break;
		} //switch
		cout<<somecard.clr;
		cout<<" ["<<somecard.number<<"]";
		nums[somecard.number]++;
		clrs[static_cast<int>(somecard.clr)]++;

   }cout<<endl;

   int i=0;
   const Card* plr=gameSession.players[0].getHand();cout<<"Hand1: \n";
   while(plr[i].number!=11)
   {
	   nums[plr[i].number]++;
	   clrs[static_cast<int>(plr[i].clr)]++;
	   cout<<plr[i].clr<<" ["<<plr[i].number<<"]\n";
	   i++;
   }
   i=0;
   const Card* plr2=gameSession.players[1].getHand();cout<<"Hand2: \n";
   while(plr2[i].number!=11)
   {
	   nums[plr2[i].number]++;
	   clrs[static_cast<int>(plr2[i].clr)]++;
	   cout<<plr[i].clr<<" ["<<plr2[i].number<<"]\n";
	   i++;
   }


   for(int i=0;i<10;i++)
   {
	   cout<<nums[i]<<" ";
   }
   cout<<"\n";
   for(int i=0;i<5;i++)
   {
	   cout<<clrs[i]<<" ";
   }
}
*/

int main()
{
	srand(time(NULL));
	Game gameSession;               //players declared . Cards drawn. First card put on table.
	while (!gameSession.nextTurn()) //while there is no winner
	{
		// :)
	}
	cout << " And the big winner is Player " << gameSession.getPlayerRound() + 1 << " !\n";

	//print(gameSession);
	//print(gameSession);
	//cout<<"\nEND\n";

	return 0;
}