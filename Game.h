#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "pch.h"
#include <vector>
#include "BattleshipUtilities.h"
#include "ConsoleDisplay.h"
#include "Boardtile.h"
#include "Ship.h"

class BoardTile;
class Ship;
class ConsoleDisplay;

class Game {
public:
	Game();
	Game(util::DifficultyLevel difficulty);
	~Game();

	void nextMove();
	bool gameOver();

	void setDisplay(ConsoleDisplay *display);
	BoardTile* getBoardTile(int tile_id);
	int getTotalNumOfMoves();
	
private:
	void createBoard();
	void createShips();
	bool shipFits(int row, int col, int direction, int ship_size);
	bool shipCollision(int row, int col, int direction, int ship_size, int temp_ship_tiles[]);
	bool inputCorrect(char guess_row, int guess_col);
	void placeShipOnBoard(util::ShipType ship_type);

	ConsoleDisplay* m_display;
	std::vector<Ship*> m_ships;
	std::vector<BoardTile*> m_board_tiles;
	int m_board_size;
	int m_ship_num;
	int m_num_of_tiles_with_ship;
	int m_total_moves_num;
	util::DifficultyLevel m_difficulty;
};

#endif _GAME_H