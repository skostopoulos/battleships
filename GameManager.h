#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "BattleshipUtilities.h"
#include "ConsoleDisplay.h"

class Game;
class ConsoleDisplay;

class GameManager {
public:
	void initGame();
	void playGame();
	bool restartGame();

private:
	int selectDifficultyLevel();
	Game *m_game;
	ConsoleDisplay *m_display;
	util::DifficultyLevel m_difficulty_level;
};

#endif _GAMEMANAGER_H
