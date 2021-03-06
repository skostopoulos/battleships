#include "pch.h"
#include "GameManager.h"
#include "Game.h"

#include <iostream>

using namespace std;

bool checkLevelInput(int level_input);

void GameManager::initGame(){

	ConsoleDisplay::greetUser();

	int level = selectDifficultyLevel();
	m_difficulty_level = (util::DifficultyLevel)level;

	m_game    = new Game(m_difficulty_level);
	m_display = new ConsoleDisplay(m_difficulty_level, m_game);

	m_game->setDisplay(m_display);
}

void GameManager::playGame()
{	
	do{
		m_game->nextMove();
	} while (!(m_game->gameOver()));
}

bool GameManager::restartGame()
{
	bool retval = false;
	char answer;
	cout << "Would you like to play again? (y/n)" << endl;
	do
	{
		cin >> answer;
		if (cin.fail()) {
			cin.clear();
			continue;
		}
	} while (answer != 'y' && answer != 'n');

	if (answer == 'y') {
		retval = true;
	}
	
	delete m_game;
	delete m_display;
	return retval;
}


// Private functions

int GameManager::selectDifficultyLevel() {

	int level_input;

	do {
		ConsoleDisplay::printDifficultyLevelOptions();
		cin >> level_input;
		if (cin.fail()) {
			cin.clear();
			continue;
		}
	} while (!checkLevelInput(level_input));

	return level_input;
}

bool checkLevelInput(int level_input) {

	if (level_input != util::EASY && level_input != util::MEDIUM && level_input != util::HARD) {
		return false;
	}
	return true;
}
