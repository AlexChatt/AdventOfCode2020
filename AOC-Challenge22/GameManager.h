#pragma once

#include <queue>
#include <iostream>
#include <string>
#include <fstream>

class GameManager
{
private:

	int DeckSize = 0;

	std::queue<uint16_t> Player1Deck;
	std::queue<uint16_t> Player2Deck;

	void PlayGame();

public:

	bool FillDecks(const std::string FileName);

	uint64_t GetFinalPlayerScore();

};