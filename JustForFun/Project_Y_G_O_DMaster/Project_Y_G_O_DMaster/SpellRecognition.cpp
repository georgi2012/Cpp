#include "SpellsRecognition.h"

SpellName SpellRecognition::recognize(std::string _name, std::string& _cardText, std::vector<std::string>& _cardOutlook)
{
	if (_cardOutlook.size() < 19) {
		_cardOutlook.resize(10);
	}
	for (unsigned i = 0; i < _name.size(); i++) {
		if (_name[i] >= 'A' && _name[i] <= 'Z') {
			_name[i] -= 'A' - 'a';
		}
	}
	if (_name == "monster reborn") {
		_cardText = "Special summon a monster from either your's or your oponent's graveyard.";
		_cardOutlook[5] = "| Summon one|";
		_cardOutlook[6] = "|  monster  |";
		_cardOutlook[7] = "|from any GY|";
		_cardOutlook[8] = "|           |";
		return SpellName::MonsterReborn;
	}
	else if (_name == "fissure") {
		_cardText = "Destroy the one face up enemy monster with the lowest ATK.";
		_cardOutlook[5] = "|Destroy the|";
		_cardOutlook[6] = "|enemy monst|";
		_cardOutlook[7] = "|with lowest|";
		_cardOutlook[8] = "|    ATK    |";
		return SpellName::Fissure;
	}
	else if (_name == "pot of greed") {
		_cardText = "Draw two cards from your deck.";
		_cardOutlook[5] = "|   Draw    |";
		_cardOutlook[6] = "| two cards |";
		_cardOutlook[7] = "| from your |";
		_cardOutlook[8] = "|   deck    |";
		return SpellName::PotOfGreed;
	}

	else {
		return SpellName::unknown;
	}
}