#pragma once
#include <string>
#include <vector>
enum class SpellName {
	unknown = -1,
	MonsterReborn=0,
	Fissure=1,
	PotOfGreed=2
};

class SpellRecognition {
private:
	//SpellName spellName = SpellName::unknown;

public:
	SpellRecognition() = default;
	virtual ~SpellRecognition() = default;
	SpellName recognize(std::string _name,std::string& _cardText, std::vector<std::string>& _cardOutlook);
};
