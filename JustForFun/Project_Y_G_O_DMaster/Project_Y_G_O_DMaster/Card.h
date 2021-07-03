#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SpellsRecognition.h"
class Card {
protected:
	std::string cardName;
	std::vector<std::string> cardOutlook;
	bool isMonster=true;

	virtual void generateOutlook() = 0;
public:
	bool isSet = false;
	Card(std::string name,bool _isMonster);
	Card(const Card& other);
	virtual ~Card()=default;
	std::string getCardName() const;
	bool isMonsterCheck() const;
	std::vector<std::string> getCardOutlook;
	std::string getCardOutlookLine(short line) const;
	std::string getCardOutlookLineAsSet(short line) const;
	void printOutlook();
};

class MonsterCard :public Card {
protected:
	unsigned attack;
	unsigned defense;
	unsigned short stars;

	virtual void generateOutlook() override;
public:
	MonsterCard(std::string name,unsigned attack,unsigned defense,unsigned short stars);
	unsigned getAttack() const;
	unsigned getDefense() const;
	unsigned short getStars() const;

};

class SpellCard :public Card ,private SpellRecognition {
protected:
	std::string cardText;
	SpellName spellType;
	virtual void generateOutlook() override;
public:
	SpellCard(std::string name);
	std::string getCardText() const;

};