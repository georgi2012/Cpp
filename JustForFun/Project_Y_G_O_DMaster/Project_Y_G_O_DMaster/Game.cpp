#include "Game.h"
using std::cout;
using std::endl;

Game::~Game()
{
	delete firstPlayer;
	delete secondPlayer;
}

Game& Game::getInstance()
{
	return instance;
}

void Game::loadPlayerOne(std::string filePath, unsigned deckSize, int LifePoints)
{
	try {
		firstPlayer = new Player(filePath, deckSize, LifePoints, true);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Fatal error::Couldn't create the player!\n");
	}
}

void Game::loadPlayerTwo(std::string filePath, unsigned deckSize, int LifePoints)
{
	try {
		secondPlayer = new Player(filePath, deckSize, LifePoints, false);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Fatal error::Couldn't create the player!\n");
	}
}

void Game::gameOn()
{
	if (firstPlayer == nullptr || secondPlayer == nullptr) {
		throw std::runtime_error("Players not set to start the game!\n");
	}

}

void Game::clearScreen()
{
	system("CLS");
}

void Game::printGameField(short arrowOffset)
{
	clearScreen();
	std::vector<Card>* playerMonsters;
	std::vector<Card>* playerSpells;
	if (isFrstPlrRound) {//firstly , it points to the enemy
		playerMonsters = &secondPlMonsters;
		playerSpells = &secondPlSpells;
	}
	else {
		playerMonsters = &firstPlMonsters;
		playerSpells = &firstPlSpells;
	}
	cout << "--------------------------Yu-Gi-Oh! Duel Masters---------------------------------------\n";
	cout << "                        (Enemy Spells/Traps Zone)\n";
	std::string line;
	for (unsigned i = 0; i < playerSpells->size(); i++) {
		line.clear();
		if ((*playerSpells)[i].isSet) {
			line += playerSpells->at(i).getCardOutlookLineAsSet(i);
		}
		else {
			line += playerSpells->at(i).getCardOutlookLine(i);
		}
	}
}

Game Game::instance;



//--------------------------Yu-Gi-Oh! Duel Masters---------------------------------------
//                        (Enemy Spells/Traps Zone)
//  ------   ------   ------                                                
// | Deck | |  GY  | | name |                                               
// |  18  | |   2  | |  or  |                                                
// |      | |      | |????? |                                                
//  ------   ------   ------                                               
//                            (Enemy Monsters)
//0    -----------  
//1   |			8*|    <--(23 chars)-->
//2   |Blue eyes  |  ---------------------
//3   |White      | |			        8*|
//4   |dragon     | |Blue Eyes White      |
//5   |			  | |Dragon               |
//6   |	          | |			          |
//7   |ATK:3000   | |ATK:3000     Def:2500|
//8   |DEF:2500	  |  ---------------------
//9    -----------   
//-------------------------------------------------------------------------------------
//                            (Your Monsters)
//0    -----------  
//1   |			8*| 
//2   |Blue eyes  |  ---------------------
//3   |White      | |			        8*|
//4   |dragon     | |Blue Eyes White      |
//5   |			  | |Dragon               |
//6   |	          | |			          |
//7   |ATK:3000   | |ATK:3000     Def:2500|
//8   |DEF:2500	  |  ---------------------
//9    -----------   
//
//                        (Your Spells/Traps Zone)
//  ------   ------   ------                                                
// | Deck | |  GY  | | name |                                               
// |  16  | |   8  | |  or  |                                                
// |      | |      | |????? |                                                
//  ------   ------   ------                                                 
//-----------------------------Your Hand----------------------------------------------------
// -----------   -----------   -----------   -----------   -----------
//|  ~Spell~  | |  ~Spell~  | |        12*| |         8*| |         7*|
//|Pot of     | |Pot of     | |Obelisk    | |Blue eyes  | |Dark       |
//|Greed      | |Greed      | |the        | |White      | |Magician   |
//|           | |           | |Tomentor   | |dragon     | |           |
//|   Draw    | |   Draw    | |           | |           | |           |
//| two cards | | two cards | |           | |           | |           |
//| from your | | from your | |ATK:4000   | |ATK : 3000 | |ATK : 2500 |
//|   deck    | |   deck    | |DEF : 4000 | |DEF : 2500 | |DEF : 2100 |
// -----------   -----------   -----------   -----------   -----------
//      ^
//     Your
//    Choice
//(More detailed info about the selected spell)
//
//(Use < > to navigate to your choice and use Enter to play the card)



















