#ifndef _CONSOLEDISPLAY_H
#define _CONSOLEDISPLAY_H
#pragma once

#include "pch.h"
#include "Game.h"
#include <string>
#include "BoardTile.h"

class Game;

class ConsoleDisplay {
public:
	ConsoleDisplay();
	ConsoleDisplay(util::DifficultyLevel level, Game *game);

	static void greetUser();
	static void printDifficultyLevelOptions();

	void displayBoard();
	void clearScreen();
	void saveMessageFromPreviousMove(std::string output_message);
	void printSavedMessage();
	void printWrongInputMessage();
	void printWinMessage();
	void printTile(int tile_id);
	void printRowName(int col);

private:
	void calculateRowsForDisplayBoard();
	void printFleet();
	std::string m_message;
	std::string m_first_row;
	std::string m_second_row;
	std::string m_row_separator;
	int m_board_size;
	util::DifficultyLevel m_level;
	util::Fleet m_fleet;
	Game *m_game;
};

#endif CONSOLEDISPLAY_H