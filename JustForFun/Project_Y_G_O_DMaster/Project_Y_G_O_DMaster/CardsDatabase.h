#pragma once
#include "Card.h"
#include <fstream>
//#include <tuple>

class CardsDatabase {
protected:
	//std::vector<std::tuple<std::string, unsigned, unsigned,unsigned short>> monsters;//name attack defense stars
	//std::vector<std::string> spells;// name
	std::vector<MonsterCard> monsters;
	std::vector<SpellCard> spells;
	//search spells by name from the list , if not existing throw error
	MonsterCard makeCard(std::string name, unsigned atk, unsigned def, unsigned short stars);
	SpellCard makeCard(std::string name);//checks if exists
	void addCard(std::string card, bool isMonster);
public:
	CardsDatabase() = default;
	virtual ~CardsDatabase() = default;
	void loadDatabase(std::string fileName);
	void printCards();
	int getAllCardsNum();
	const Card* operator[](unsigned index);

};