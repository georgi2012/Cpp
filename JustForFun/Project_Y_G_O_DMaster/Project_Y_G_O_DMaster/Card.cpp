#include "Card.h"

Card::Card(std::string name, bool _isMonster)
{
	cardName = name;
	isMonster = _isMonster;
}

Card::Card(const Card& other) :cardName(other.cardName), cardOutlook(other.cardOutlook)
{
}

std::string Card::getCardName() const
{
	return cardName;
}

bool Card::isMonsterCheck()const
{
	return isMonster;
}
std::string Card::getCardOutlookLine(short line) const
{
	return cardOutlook[line];
}
std::string Card::getCardOutlookLineAsSet(short line) const
{
	//are set
	if (isMonster) {
		if (line == 2 || line == 8) {
			return " --------------------- ";
		}
		else if (line == 4) {
			return "|      (Unknown)      |";
		}
		else if (line > 2 && line < 8) {
			return "|			          |";
		}
		else return " 			           ";
	}
	else {//spells 
		if (line == 0 || line == 9) {
			return " ----------- ";
		}
		else if (line == 4) {
			return  "|  (Unknown) |";
		}
		else return "|			  |";
	}

}
void Card::printOutlook()
{
	for (unsigned i = 0; i < cardOutlook.size(); i++) {
		std::cout << cardOutlook[i] << std::endl;
	}
}
//    -----13------
// space for name-> 11 char per line
//0    -----------
//1   |			8*|
//2   |Blue eyes  |
//3   |White      |
//4   |dragon     |
//5   |			  |
//6   |	          |
//7   |ATK:3000   |
//8   |DEF:2500	  |
//9    -----------

void MonsterCard::generateOutlook()
{
	cardOutlook.resize(10);
	cardOutlook[0] = " ----------- ";
	cardOutlook[1] = "|        ";
	if (stars < 10) {
		cardOutlook[1].push_back(' ');
	}
	cardOutlook[1] += std::to_string(stars) + "*|";
	//
	//std::cout << cardOutlook[0] << std::endl;
	//std::cout << cardOutlook[1]<<std::endl;
	//
	std::string name;
	int i = 0;
	if (cardName.size() <= 11) {
		cardOutlook[2] = "|" + cardName;
		for (i = 0; i < 11 - cardName.size(); i++) {
			cardOutlook[2].push_back(' ');
		}
		cardOutlook[2].push_back('|');
	}
	else {
		unsigned lastSpacePlace = 0;
		unsigned short currentVectorLine = 2;
		unsigned short lineStart = 0;
		while (i < cardName.size()) {
			if (((i - lineStart + 1) % 11) == 0) {//time for a new line
				if (lastSpacePlace != 0) {
					cardOutlook[currentVectorLine] = "|" + cardName.substr(lineStart, lastSpacePlace - lineStart);
					for (int j = 0; j < 11 - (lastSpacePlace - lineStart); j++)
					{
						cardOutlook[currentVectorLine].push_back(' ');
					}
					cardOutlook[currentVectorLine].push_back('|');
					currentVectorLine++;
					lineStart = lastSpacePlace + 1;
					lastSpacePlace = 0;
					//
					//std::cout << cardOutlook[currentVectorLine-1] << std::endl;
					//
				}
				else {
					cardOutlook[currentVectorLine] = '|' + cardName.substr(lineStart, 11) + '|';
					currentVectorLine++;
					lineStart = i;
				}
			}
			if (cardName[i] == ' ') {
				lastSpacePlace = i;
			}
			i++;
		}
		cardOutlook[currentVectorLine] = '|' + cardName.substr(lineStart);
		for (int j = 0; j < (int)(11 - (cardName.size() - lineStart)); j++) {
			cardOutlook[currentVectorLine].push_back(' ');
		}
		cardOutlook[currentVectorLine].push_back('|');
		//
		//std::cout << cardOutlook[currentVectorLine] << std::endl;
		//
		/*currentVectorLine++;
		for (; currentVectorLine < 7; currentVectorLine++) {
			cardOutlook[currentVectorLine] = "|           |";
		}*/
	}
	{
		unsigned lineIndex = 2;
		while (lineIndex < 7) {
			if (cardOutlook[lineIndex].empty()) {
				cardOutlook[lineIndex] = "|           |";
			}
			lineIndex++;
		}
	}
	//|ATK:3000   |
	cardOutlook[7] = "|ATK:" + std::to_string(attack);
	for (unsigned i = 0; i < 7 - (std::to_string(attack)).size(); i++) {
		cardOutlook[7].push_back(' ');
	}
	cardOutlook[7].push_back('|');
	//
	//std::cout << cardOutlook[7] << std::endl;
	//
	cardOutlook[8] = "|DEF:" + std::to_string(defense);
	for (unsigned i = 0; i < 7 - (std::to_string(defense)).size(); i++) {
		cardOutlook[8].push_back(' ');
	}
	cardOutlook[8].push_back('|');
	//
	//std::cout << cardOutlook[8] << std::endl;
	//
	cardOutlook[9] = " ----------- ";

}

MonsterCard::MonsterCard(std::string name, unsigned attack, unsigned defense, unsigned short stars) :
	Card(name, true), attack(attack), defense(defense), stars(stars)
{
	generateOutlook();
}

unsigned MonsterCard::getAttack()const
{
	return attack;
}

unsigned MonsterCard::getDefense()const
{
	return defense;
}

unsigned short MonsterCard::getStars()const
{
	return stars;
}

//    -----13------
// space for name-> 11 char per line
//0    -----------
//1   |  ~Spell~  |
//2   |Monster    |
//3   |Reborn     |
//4   |           |
//5   | Summon one|
//6   |  monster  |
//7   |from any GY|
//8   |           |
//9    -----------
//Monster Reborn
void SpellCard::generateOutlook()
{
	cardOutlook[0] = " ----------- ";
	cardOutlook[1] = "|  ~Spell~  |";
	cardOutlook[9] = " ----------- ";
	if (cardName.size() <= 11) {
		cardOutlook[2] = "|" + cardName;
		for (int i = 0; i < 11 - cardName.size(); i++) {
			cardOutlook[2].push_back(' ');
		}
		cardOutlook[2].push_back('|');
	}
	else {
		unsigned lastSpacePlace = 0;
		unsigned short currentVectorLine = 2;
		unsigned short lineStart = 0;
		int i = 0;
		while (i < cardName.size()) {
			if (((i - lineStart + 1) % 11) == 0) {//time for a new line
				if (lastSpacePlace != 0) {
					cardOutlook[currentVectorLine] = "|" + cardName.substr(lineStart, lastSpacePlace - lineStart);
					for (int j = 0; j < 11 - (lastSpacePlace - lineStart); j++)
					{
						cardOutlook[currentVectorLine].push_back(' ');
					}
					cardOutlook[currentVectorLine].push_back('|');
					currentVectorLine++;
					lineStart = lastSpacePlace + 1;
					lastSpacePlace = 0;
					//
					//std::cout << cardOutlook[currentVectorLine-1] << std::endl;
					//
				}
				else {
					cardOutlook[currentVectorLine] = '|' + cardName.substr(lineStart, 11) + '|';
					currentVectorLine++;
					lineStart = i;
				}
			}
			if (cardName[i] == ' ') {
				lastSpacePlace = i;
			}
			i++;
		}
		cardOutlook[currentVectorLine] = '|' + cardName.substr(lineStart);
		for (int j = 0; j < (int)(11 - (cardName.size() - lineStart)); j++) {
			cardOutlook[currentVectorLine].push_back(' ');
		}
		cardOutlook[currentVectorLine].push_back('|');
		//
		//std::cout << cardOutlook[currentVectorLine] << std::endl;
		//
		/*currentVectorLine++;
		for (; currentVectorLine < 5; currentVectorLine++) {
			cardOutlook[currentVectorLine] = "|           |";
		}*/
	}
	{
		unsigned lineIndex = 2;
		while (lineIndex < 5) {
			if (cardOutlook[lineIndex].empty()) {
				cardOutlook[lineIndex] = "|           |";
			}
			lineIndex++;
		}
	}
}

SpellCard::SpellCard(std::string name) :
	Card(name, false)
{
	spellType = recognize(name, cardText, cardOutlook);
	if (spellType == SpellName::unknown) {
		throw std::runtime_error("Invalid spell with name " + name + "!\n");
	}
	generateOutlook();
}

std::string SpellCard::getCardText()const
{
	return cardText;
}