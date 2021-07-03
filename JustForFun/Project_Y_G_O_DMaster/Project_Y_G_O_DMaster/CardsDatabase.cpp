#include "CardsDatabase.h"
using std::cout;

MonsterCard CardsDatabase::makeCard(std::string name, unsigned atk, unsigned def, unsigned short stars)
{
	MonsterCard monster(name, atk, def, stars);
	return monster;
}

SpellCard CardsDatabase::makeCard(std::string name)
{
	//search in base
	SpellCard spell(name);
	return spell;
}

void CardsDatabase::addCard(std::string card, bool isMonster)
{
	if (card.empty()) {
		return;
	}
	if (isMonster) {//name+attack+defense+stars
		unsigned attack = 0, defense = 0;
		unsigned short stars = 0;
		std::string str;
		int i = card.size() - 1;
		while (i >= 0 && card[i] != ' ')//stars
		{
			if (card[i] < '0' || card[i]>'9') {
				throw std::invalid_argument("Monster stars invalid format.\n");
			}
			//str.push_back(card[i]);
			i--;
		}
		str = card.substr(i + 1);
		card.erase(i, card.size() - i);
		if (str.size() >= 3) {
			throw std::invalid_argument("Monster invalid format.Too many stars.\n");
		}
		else if (str == "0")
		{
			throw std::invalid_argument("Monster invalid format.0 stars monster.\n");
		}
		stars = std::stoi(str);
		i--;
		while (i >= 0 && card[i] != ' ')//defense
		{
			if (card[i] < '0' || card[i]>'9') {
				throw std::invalid_argument("Monster defense invalid format.\n");
			}
			i--;
		}
		str = card.substr(i + 1);
		card.erase(i, card.size() - i);
		defense = std::stoi(str);
		i--;
		while (i >= 0 && card[i] != ' ')//attack
		{
			if (card[i] < '0' || card[i]>'9') {
				throw std::invalid_argument("Monster attack invalid format.\n");
			}
			i--;
		}
		str = card.substr(i + 1);
		card.erase(i, card.size() - i);
		attack = std::stoi(str);
		//str is now the name
		//monsters.push_back(std::make_tuple(card, attack, defense, stars));
		//std::tuple<std::string, unsigned, unsigned,unsigned short> newCard = std::make_tuple(str, attack, defense,stars);
		monsters.push_back(makeCard(card, attack, defense, stars));

	}
	else {//spell 
		//-search in the database for the card name
		spells.push_back(makeCard(card));
	}
}

void CardsDatabase::loadDatabase(std::string fileName)
{
	std::ifstream file(fileName);
	if (!file) {
		throw std::runtime_error("Couldn't open file.\n");
	}
	std::string line; //each line to be different card
	bool isMonster;
	std::getline(file, line);
	if (line == "-Monsters:")
	{
		isMonster = true;
	}
	else if (line == "-Spells:") {
		isMonster = false;
	}
	else {
		std::cout << "Cards in file should be grouped as -Monsters: and -Spells: , each card should be on \
a different line . For monsters it's name+attack+defense , for spells it's just the name.";
		throw std::runtime_error("Invalid format.\n");
	}
	while (std::getline(file, line)) {
		if (isMonster && line == "-Spells:") {
			isMonster = false;
		}
		else {
			try {
				addCard(line, isMonster);
			}
			catch (const std::invalid_argument& e) {
				//no such spell? Not valid Monster format
				//should we catch it
			}
		}
	}

}

void CardsDatabase::printCards()
{
	unsigned short maxNameLenght = 0;
	//unsigned short maxSpellNameLenght = 0;
	unsigned short maxAttackLenght = 0;
	unsigned short maxDefenseLenght = 0;
	for (unsigned i = 0; i < monsters.size(); i++) {
		if (monsters[i].getCardName().size() > maxNameLenght) {
			maxNameLenght = monsters[i].getCardName().size();
		}
		if (std::to_string(monsters[i].getAttack()).size() > maxAttackLenght) {
			maxAttackLenght = std::to_string(monsters[i].getAttack()).size();
		}
		if (std::to_string(monsters[i].getDefense()).size() > maxDefenseLenght) {
			maxDefenseLenght = std::to_string(monsters[i].getDefense()).size();
		}
	}
	/*for (unsigned i = 0; i < spells.size(); i++) {
		if (spells[i].getCardName().size() > maxSpellNameLenght) {
			maxSpellNameLenght = spells[i].getCardName().size();
		}
	}*/
	unsigned short diff = 0;
	std::cout << "-Monsters:\n";
	for (unsigned i = 0; i < monsters.size(); i++) {
		std::cout << "(" << monsters[i].getCardName() << ")";
		diff = maxNameLenght - monsters[i].getCardName().size();
		for (int j = 0; j < diff + 1; j++) {
			std::cout << " ";
		}
		std::cout << "ATK:" << monsters[i].getAttack();
		diff = maxAttackLenght - std::to_string(monsters[i].getAttack()).size();
		for (int j = 0; j < diff; j++) {
			std::cout << " ";
		}
		diff = maxDefenseLenght - std::to_string(monsters[i].getDefense()).size();

		std::cout << " DEF:" <<monsters[i].getDefense();
		for (int j = 0; j < diff; j++) {
			std::cout << " ";
		}
		std::cout << " " << monsters[i].getStars() << "*\n";
		monsters[i].printOutlook();
	}
	std::cout << "\n-Spells:\n";
	if (spells.empty()) {
		std::cout << "None.\n";
		return;
	}
	for (unsigned i = 0; i < spells.size(); i++) {
		std::cout << "(" << spells[i].getCardName() << ") " << spells[i].getCardText() << "\n";
		spells[i].printOutlook();
	}
	std::cout << std::endl;

}

int CardsDatabase::getAllCardsNum()
{
	return spells.size() + monsters.size();
}

const Card* CardsDatabase::operator[](unsigned index)
{
	if (index >= getAllCardsNum()) {
		throw std::invalid_argument("Op[]: Index too big.");
	}
	if (index >= monsters.size()) {
		return &spells[index-monsters.size()];
	}
	return &monsters[index];
}
