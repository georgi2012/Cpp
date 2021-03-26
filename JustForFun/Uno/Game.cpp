#include <iostream>
//#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include "Game.h"

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;
using std::string;

Game::Game()
{
	for (int i = 0; i < 2; ++i) //2 players
	{
		for (int j = 0; j < 3; j++) //starting hand with 3 cards
		{
			players[i].drawCard(generateCard());
		}
	}
	currentCard = generateCard();
	while (currentCard.number == DRAW4_NUMBER || currentCard.number == CHANGECOLOR_NUMBER) //BLACK CARD
	{
		Card nextCard = generateCard();					  //redraw
		cardsPile.findPlaceInDeck(currentCard.number, 1); //put back in the deck
		currentCard = nextCard;
	}
	isScndRound = false;
}

void Game::printHelperNum(string *&ptr) const
{
	// string *ptr;
	switch (currentCard.number)
	{
	case 1:
	{
		ptr = new (nothrow) string[6]{R"( __ )",
									  R"(/_ |)",
									  R"( | |)",
									  R"( | |)",
									  R"( | |)",
									  R"( |_|)"};
		//ptr = number;
		return; // ptr;
	}
	case 2:
	{
		ptr = new (nothrow) string[6]{
			R"( ___  )",
			R"(|__ \ )",
			R"(   ) |)",
			R"(  / / )",
			R"( / /_ )",
			R"(|____|)"};
		//ptr = number;
		return; // ptr;
	}
	case 3:
	{
		ptr = new (nothrow) string[6]{
			R"(  ____  )",
			R"( |___ \ )",
			R"(   __) |)",
			R"(  |__ < )",
			R"(  ___) ))",
			R"( |____/ )"};
		//ptr = number;
		return; // ptr;
	}
	case 4:
	{
		ptr = new (nothrow) string[6]{
			R"(  _  _   )",
			R"( | || |  )",
			R"( | || |_ )",
			R"( |__   _|)",
			R"(    | |  )",
			R"(    |_|  )"};
		//ptr = number;
		return; // ptr;
	}
	case 5:
	{
		ptr = new (nothrow) string[6]{
			R"(  _____ )",
			R"( | ___| )",
			R"( | |__  )",
			R"( |___ \ )",
			R"(  ___) |)",
			R"( |____/)"};
		//ptr = number;
		return; // ptr;
	}
	case 6:
	{
		ptr = new (nothrow) string[6]{
			R"(    __  )",
			R"(   / /  )",
			R"(  / /_  )",
			R"( | '_ \ )",
			R"( | (_) |)",
			R"(  \___/ )"};
		//ptr = number;
		return; // ptr;
	}

	case 7:
	{
		ptr = new (nothrow) string[6]{
			R"(  ______ )",
			R"( |____  |)",
			R"(     / / )",
			R"(    / /  )",
			R"(   / /   )",
			R"(  /_/    )"};
		//ptr = number;
		return; // ptr;
	}

	case 8:
	{
		ptr = new (nothrow) string[6]{
			R"(   ___  )",
			R"(  / _ \ )",
			R"( | (_) |)",
			R"(  > _ < )",
			R"( | (_) |)",
			R"(  \___/  )"};
		//ptr = number;
		return; // ptr;
	}
	case 9:
	{
		ptr = new (nothrow) string[6]{
			R"(   ___  )",
			R"(  / _ \ )",
			R"( | (_) |)",
			R"(  \__, |)",
			R"(    / / )",
			R"(   /_/  )"};
		//ptr = number;
		return; // ptr;
	}
	case DRAW4_NUMBER:
	{
		ptr = new (nothrow) string[6]{
			R"(        _  _    )",
			R"(    _  | || |   )",
			R"(  _| |_| || |_  )",
			R"( |_   _|__   _| )",
			R"(   |_|    | |   )",
			R"(          |_|   )"

		};
		return;
	}
	case CHANGEDIR_NUMBER:
	{
		ptr = new (nothrow) string[6]{
			R"(    __          __    )",
			R"(   / /          \ \   )",
			R"(  / /   ______   \ \  )",
			R"( < <   |______|   > > )",
			R"(  \ \            / /  )",
			R"(   \_\          /_/   )"

		};
		return;
	}
	case CHANGECOLOR_NUMBER:
	{
		ptr = new (nothrow) string[6]{"", "", "", "", "", ""};
		return;
	}

	default:
		ptr = new (nothrow) string[6]{"", "", "", "", "", ""};
		return; // nullptr;
	}
}

void Game::printHelperClr(string *&ptr) const
{
	//string *ptr;
	//cout << currentCard.clr;
	switch (currentCard.clr)
	{
	case red:
	{
		ptr = new (nothrow) string[6]{
			R"(  _____          _  )",
			R"( |  __ \        | | )",
			R"( | |__) |___  __| | )",
			R"( |  _  // _ \/ _` | )",
			R"( | | \ \  __/ (_| | )",
			R"( |_|  \_\___|\__,_| )"};
		//ptr = colors;
		return; //ptr;
	}
	case blue:
	{
		ptr = new (nothrow) string[6]{
			R"(   ____  _             )",
			R"(  |  _ \| |            )",
			R"(  | |_) | |_ ___  ___  )",
			R"(  |  _ <| | | | |/ _ \ )",
			R"(  | |_) | | |_| |  __/ )",
			R"(  |____/|_|\__,_|\___| )"};
		//ptr = colors;
		return; // ptr;
	}
	case yellow:
	{
		ptr = new (nothrow) string[6]{
			R"(             | | |              )",
			R"(   _   _  ___| | | _____      __)",
			R"(  | | | |/ _ \ | |/ _ \ \ /\ / /)",
			R"(  | |_| |  __/ | | (_) \ V  V / )",
			R"(   \__, |\___|_|_|\___/ \_/\_/  )",
			R"(   |___/                        )"};

		//ptr = colors;
		return; // ptr;
	}
	case green:
	{
		ptr = new (nothrow) string[6]{
			R"(   __ _ _ __ ___  ___ _ __   )",
			R"(  / _` | '__/ _ \/ _ \ '_ \  )",
			R"( | (_| | | |  __/  __/ | | | )",
			R"(  \__, |_|  \___|\___|_| |_| )",
			R"(   __/ |                     )",
			R"(  |___/                      )"};
		//ptr = colors;
		return; // ptr;
	}
	default:
		ptr = new (nothrow) string[6]{"", "", "", "", "", ""};
		return; //nullptr;
	}
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

void printClr(COLOR index)
{
	switch (index)
	{
	case red:
		cout << " RED ";
		return;
	case blue:
		cout << " BLUE ";
		return;
	case green:
		cout << " GREEN ";
		return;
	case yellow:
		cout << " YELLOW ";
		return;

	default:
		cout << " UNKNOWN ";
		return;
	}
}

void Game::printCurentCard()
{

	string *cardNum;
	printHelperNum(cardNum);
	string *cardClr;
	printHelperClr(cardClr);
	if (!cardNum || !cardClr) //we could not allocate the memory
	{
		printClr(currentCard.clr);
		cout << " " << currentCard.number << endl;
		delete[] cardNum; // in case we had enough memory for cardNum
		return;
	}

	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << cardClr[i] << " " << cardNum[i] << endl;
	}
	cout << endl;
	delete[] cardNum;
	delete[] cardClr;
	return;
}

void Game::printColorPicker(short choice = -1) const //helper for Black cards
{
	for (int i = 1; i <= 4; i++)
	{
		cout << "\n"
			 << i - 1 << ". ";
		switch (i)
		{
		case RED:
		{
			cout << "Red ";
			break;
		}
		case BLUE:
		{
			cout << "Blue ";
			break;
		}
		case GREEN:
		{
			cout << "Green ";
			break;
		}
		case YELLOW:
		{
			cout << "Yellow ";
			break;
		}
		default:
			cout << "No such clr ";
			break;
		} //switch
		if (choice == (i - 1))
		{
			cout << " <--[ Your current choice ]";
		}
	} //for
	cout << "\n\nYou played a black card.\nPress Enter to choose this color. ";
	return;
}

void Game::printGame(const int currentChoice = -1, bool isSpecialCard = false) //special card are the black ones
{
	system("cls");
	printCurentCard();
	cout << "Player " << isScndRound + 1 << " 's turn \n";

	if (!isSpecialCard)
	{
		players[isScndRound].printHand(currentChoice);
		cout << "\n"
			 << players[isScndRound].getHandSize() << ". Draw a card.";
		if (currentChoice == players[isScndRound].getHandSize())
		{
			cout << " <--[ Your current choice ]";
			cout << "\n\nPress Enter to draw a card.";
			return;
		}
		if (currentChoice >= 0)
		{
			cout << "\n\nPress Enter to play that card. ";
			return;
		}
		return;
	}

	players[isScndRound].printHand(-1); //if special card

	return;
}

/*void fixCin()
{
	cin.clear();
	cin.ignore(100, '\n');

}*/

COLOR Game::specialCard_ChangeClr()
{
	printGame(-1, true);
	printColorPicker();
	//choosing the color to play
	int playerChoice = -1;
	char command;
	do
	{
		command = _getch();
		if (command >= '0' && command <= '3' && (command - '0') != playerChoice)
		{ //if the command is a valid option
			playerChoice = command - '0';
			printGame(playerChoice, true);
			cout << endl;
			printColorPicker(playerChoice);
		}
	} while (command != ENTER_SYMBOW || playerChoice == -1); //untill we press enter

	return static_cast<COLOR>(playerChoice + 1);
}

void Game::specialCard_ChangeDir()
{
	isScndRound = !isScndRound;
}

COLOR Game::specialCard_Draw4()
{
	for (int i = 0; i < 4; i++)
	{
		players[!isScndRound].drawCard(generateCard()); //opponent draws 4 cards
	}
	return specialCard_ChangeClr(); //we pick a new color
}

bool Game::nextTurn()
{
	printGame();
	int playerChoice = -1;
	Card removedCard;
	char command;
	do
	{ //find a valid card and play it

		/*if (!cin)
		{
			fixCin();
		}
		cin >> playerChoice;*/
		command = _getch(); //we take the symbow from the keyboard
		if (command >= '0' && command <= ('9' + 1) && players[isScndRound].playCard((command - '0'), currentCard))
		{ //if the command is a valid option
			playerChoice = command - '0';
			printGame(playerChoice);
		}

	} while (command != ENTER_SYMBOW || playerChoice == -1); //untill we press enter

	if (playerChoice == players[isScndRound].getHandSize()) //he has choisen to draw a card
	{
		players[isScndRound].drawCard(generateCard()); //draw a card or discard first + draw
	}
	else
	{																 //play a card
		removedCard = players[isScndRound].removeCard(playerChoice); //remove the card from hand

		if (removedCard.number == DRAW4_NUMBER)
		{
			currentCard.clr = specialCard_Draw4();
		}
		else if (removedCard.number == CHANGECOLOR_NUMBER)
		{
			currentCard.clr = specialCard_ChangeClr();
		}
		else if (removedCard.number == CHANGEDIR_NUMBER)
		{
			specialCard_ChangeDir();
			currentCard.clr = removedCard.clr;
		}
		else
		{
			currentCard.clr = removedCard.clr; //put on table new card
		}
		currentCard.number = removedCard.number;
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
   int clrs[6]={};
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
   while(plr[i].number!=UNKNOWN_NUM)
   {
	   nums[plr[i].number]++;
	   clrs[static_cast<int>(plr[i].clr)]++;
	   cout<<plr[i].clr<<" ["<<plr[i].number<<"]\n";
	   i++;
   }
   i=0;
   const Card* plr2=gameSession.players[1].getHand();cout<<"Hand2: \n";
   while(plr2[i].number!= UNKNOWN_NUM)
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
	Game gameSession;				//players declared . Cards drawn. First card put on table.
	while (!gameSession.nextTurn()) //while there is no winner
	{
		// :)
	}
	cout << "\n \nAnd the big winner is Player " << gameSession.getPlayerRound() + 1 << " !\n";

	//print(gameSession);
	//print(gameSession);
	//cout<<"\nEND\n";

	return 0;
}