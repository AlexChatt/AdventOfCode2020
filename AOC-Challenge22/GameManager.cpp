#include "GameManager.h"

bool GameManager::FillDecks(const std::string FileName)
{
	std::ifstream File(FileName);
	if (!File)
	{
		std::cout << "Could not find file " << FileName << std::endl;
		return false;
	}

	std::string templine;
	while (std::getline(File, templine))
	{
		if (templine == "")
		{
			break;
		}
		else if (templine.find(":") == std::string::npos)
		{
			Player1Deck.push(std::stoi(templine));
		}
	}

	while (std::getline(File, templine))
	{
		if (templine == "")
		{
			break;
		}
		else if (templine.find(":") == std::string::npos)
		{
			Player2Deck.push(std::stoi(templine));
		}
	}

	DeckSize = Player1Deck.size() + Player2Deck.size();
}

uint64_t GameManager::GetFinalPlayerScore()
{
	uint64_t FinalScore = 0;

	PlayGame();

	int Mulitplier = 1;

	std::vector<uint16_t> WinningDeck;

	if (Player1Deck.size() > Player2Deck.size())
	{
		while (Player1Deck.size() > 0)
		{
			WinningDeck.push_back(Player1Deck.front());
			Player1Deck.pop();
		}
	}
	else
	{
		while (Player2Deck.size() > 0)
		{
			WinningDeck.push_back(Player2Deck.front());
			Player2Deck.pop();
		}
	}

	for (int i = WinningDeck.size()-1; i >= 0; i--)
	{
		FinalScore += WinningDeck[i] * Mulitplier;
		Mulitplier++;
	}

	return FinalScore;
}

void GameManager::PlayGame()
{
	if (Player1Deck.size() == DeckSize ||
		Player2Deck.size() == DeckSize)
	{
		return;
	}

	uint16_t Player1Card = Player1Deck.front();
	Player1Deck.pop();
	
	uint16_t Player2Card = Player2Deck.front();
	Player2Deck.pop();

	if (Player1Card > Player2Card)
	{
		Player1Deck.push(Player1Card);
		Player1Deck.push(Player2Card);
	}
	else if (Player2Card > Player1Card)
	{
		Player2Deck.push(Player2Card);
		Player2Deck.push(Player1Card);
	}

	PlayGame();
}