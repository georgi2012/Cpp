#define CATCH_CONFIG_MAIN  
#include "Card.h"
#include "catch.hpp"

TEST_CASE("Outlook test") {
	SECTION("Monster card") {
		MonsterCard monster("Blue eyes White dragon",3000,2500,8);
		monster.printOutlook();
		MonsterCard monster2("Obelisk the Tormentor" ,4000 ,4000, 12);
		monster2.printOutlook();
		MonsterCard monster3("Some Token", 100, 0, 1);
		monster3.printOutlook();
	}
	SECTION("Spell card") {
		SpellCard spell("Monster Reborn");
		spell.printOutlook();
		SpellCard spell2("Pot of Greed");
		spell2.printOutlook();
		SpellCard spell3("Fissure");
		spell3.printOutlook();
	}
}