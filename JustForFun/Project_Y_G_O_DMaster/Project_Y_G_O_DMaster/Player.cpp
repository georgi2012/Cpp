#include "Player.h"

Player::Player(std::string filePath, unsigned deckSize, int LifePoints, bool isPlayerOne) :
	Deck(filePath, deckSize), lifePoints(LifePoints), isPlayerOne(isPlayerOne)
{
	for (short i = 0; i < 5; i++) {
		hand.push_back(draw());
	}
}

int Player::getLP() const
{
	return lifePoints;
}

bool Player::isFirstPlayer() const
{
	return isPlayerOne;
}

void Player::displayHand()
{
	std::string line;
	for (unsigned i = 0; i < 10; i++) {
		line.clear();
		for (unsigned j = 0; j < hand.size(); j++) {
			line += hand[j]->getCardOutlookLine(i) + " ";
		}
		std::cout << line << std::endl;
	}
}

const Card* Player::attemptCardPlay(short index)
{
	//display hand to be already called
	//check if hand is empty before that
		/*std::cout << std::setw(ARROW_START_POS) << "^";
		std::cout << std::setw(ARROW_START_POS) << "|";
		std::cout << std::setw(ARROW_START_POS - 2) << "(Your";
		std::cout << std::setw(ARROW_START_POS - 3) << "Choice)";*/
	attemptCardIndex = index;
	return hand[index];
}

void Player::resolveCardPlay(short discardIndex)
{
	if (discardIndex >= 0) {
		hand.erase(hand.begin() + discardIndex);
		return;
	}

	hand.erase(hand.begin() + attemptCardIndex);
	attemptCardIndex = -1;

}

