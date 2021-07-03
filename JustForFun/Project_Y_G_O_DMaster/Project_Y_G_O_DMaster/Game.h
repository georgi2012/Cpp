#pragma once
#include "Player.h"
#include "windows.h"//clears scr
//singleton
class Game {
private:
	Player* firstPlayer=nullptr;
	Player* secondPlayer=nullptr;
	std::vector<Card> firstPlMonsters;
	std::vector<Card> firstPlSpells;
	std::vector<Card> secondPlMonsters;
	std::vector<Card> secondPlSpells;
	bool isFrstPlrRound = true;

	Game()=default;
	static Game instance;

public:
	Game(const Game&) = delete;
	Game operator=(const Game&) = delete;
	~Game();
	static Game& getInstance();
	void loadPlayerOne(std::string filePath, unsigned deckSize, int LifePoints);
	void loadPlayerTwo(std::string filePath, unsigned deckSize, int LifePoints);
	void gameOn();//start the game
	void clearScreen();
	void printGameField(short arrowOffset = 0);
};