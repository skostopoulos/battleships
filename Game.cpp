#include "pch.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Game.h"
#include "Ship.h"
#include "ConsoleDisplay.h"


using namespace std;

Game::Game() {

	m_board_size			 = util::difficultyToBoardSize(util::default_difficulty_level);
	m_ship_num				 = util::difficultyToShipNum(util::default_difficulty_level);
	m_num_of_tiles_with_ship = 0;
	m_total_moves_num		 = 0;
	m_difficulty			 = util::default_difficulty_level;

	createBoard();
	createShips();
}

Game::Game(util::DifficultyLevel difficulty) {

	m_board_size             = util::difficultyToBoardSize(difficulty);
	m_ship_num               = util::difficultyToShipNum(difficulty);
	m_num_of_tiles_with_ship = 0;
	m_total_moves_num		 = 0;
	m_difficulty			 = difficulty;

	createBoard();
	createShips();
}

Game::~Game() {
	// Delete all board tiles
	for (size_t i = 0; i < m_board_tiles.size(); i++) {
		delete m_board_tiles[i];
	}
	m_board_tiles.clear();

	// Delete all ships
	for (size_t i = 0; i < m_ships.size(); i++) {
		delete m_ships[i];
	}
	m_ships.clear();

	return;
}


void Game::nextMove() {

	m_total_moves_num++;

	m_display->clearScreen();
	m_display->displayBoard();
	m_display->printSavedMessage();
	cout << "Take a guess: ";

	char guess_row;
	int guess_col;
	do {
		std::cin >> guess_row >> guess_col;
		if (cin.fail()) {
			m_display->clearScreen();
			m_display->displayBoard();
			m_display->printWrongInputMessage();
			cin.clear();
			continue;
		}
	} while (!inputCorrect(guess_row, guess_col));


	// Convert input to tile id
	int row = util::convertCharRowtoInt(toupper(guess_row));
	int col = guess_col - 1;
	int board_tile_id = row * m_board_size + col;

	if (m_board_tiles[board_tile_id]->isBombed()) {
		m_display->saveMessageFromPreviousMove("    You have already tried this tile, try a new one!\n");
	}
	else {
		m_board_tiles[board_tile_id]->setBombed(true);
		if (m_board_tiles[board_tile_id]->hasShip()) {
			m_display->saveMessageFromPreviousMove("    Congratulations! You hit a ship!\n");
			m_num_of_tiles_with_ship--;
			if (gameOver()) {
				m_display->printWinMessage();
			}
		}
		else {
			m_display->saveMessageFromPreviousMove("    No luck here! Try again!\n");
		}

	}
}

bool Game::gameOver() {

	if (m_num_of_tiles_with_ship == 0) {
		return true;
	}
	return false;
}


void Game::setDisplay(ConsoleDisplay *display) {
	m_display = display;
}

BoardTile* Game::getBoardTile(int tile_id) {
	return this->m_board_tiles[tile_id];
}

int Game::getTotalNumOfMoves() {
	return m_total_moves_num;
}


// Private functions

void Game::createBoard() {

	for (int i = 0; i < m_board_size*m_board_size; i++) {
		BoardTile* board_tile = new BoardTile();
		m_board_tiles.push_back(board_tile);
	}
}

void Game::createShips() {
	
	util::Fleet fleet = util::difficultyLevelToFleet(m_difficulty);

	// Create Carriers
	for (int i = 0; i < fleet.num_of_carriers; i++) {
		Ship* ship = new Ship(util::CARRIER);
		placeShipOnBoard(util::CARRIER);
		m_ships.push_back(ship);
		m_num_of_tiles_with_ship = m_num_of_tiles_with_ship + util::shipTypeToShipSize(util::CARRIER);
	}

	// Create Destroyers
	for (int i = 0; i < fleet.num_of_destroyers; i++) {
		Ship* ship = new Ship(util::DESTROYER);
		placeShipOnBoard(util::DESTROYER);
		m_ships.push_back(ship);
		m_num_of_tiles_with_ship = m_num_of_tiles_with_ship + util::shipTypeToShipSize(util::DESTROYER);
	}

	// Create Battleships
	for (int i = 0; i < fleet.num_of_battleships; i++) {
		Ship* ship = new Ship(util::BATTLESHIP);
		placeShipOnBoard(util::BATTLESHIP);
		m_ships.push_back(ship);
		m_num_of_tiles_with_ship = m_num_of_tiles_with_ship + util::shipTypeToShipSize(util::BATTLESHIP);
	}
}

bool Game::shipFits(int row, int col, int direction, int ship_size) {

	bool fits = false;
	switch (direction) {
	case util::UP:    if (row - (ship_size - 1) >= 0)           { fits = true; } break;
	case util::DOWN:  if (row + (ship_size - 1) < m_board_size) { fits = true; } break;
	case util::LEFT:  if (col - (ship_size - 1) >= 0)			{ fits = true; } break;
	case util::RIGHT: if (col + (ship_size - 1) < m_board_size) { fits = true; } break;
	}
	return fits;
}

bool Game::shipCollision(int row, int col, int direction, int ship_size, int temp_ship_tiles[]) {

	int tile_id;
	switch (direction) {
	case util::UP:
	case util::DOWN:
		for (int i = 0; i < ship_size; i++) {
			tile_id = (row + i) * m_board_size + col;
			temp_ship_tiles[i] = tile_id;
			if (m_board_tiles[tile_id]->hasShip()) {
				return true;
			}
		}
		break;
	case util::LEFT:
	case util::RIGHT:
		for (int i = 0; i < ship_size; i++) {
			tile_id = row * m_board_size + (col + i);
			temp_ship_tiles[i] = tile_id;
			if (m_board_tiles[tile_id]->hasShip()) {
				return true;
			}
		}
		break;
	}
	return false;

}

bool Game::inputCorrect(char guess_row, int guess_col) {

	if (isalpha(guess_row)) {
		int row = util::convertCharRowtoInt(toupper(guess_row)) + 1;
		if (row > 0 && row <= m_board_size) {
			if (guess_col > 0 && guess_col <= m_board_size) {
				return true;
			}
		}
	}

	return false;
}

void Game::placeShipOnBoard(util::ShipType ship_type) {

	int ship_size = util::shipTypeToShipSize(ship_type);
	int row, col, direction;
	int temp_ship_tiles[5] = {0,0,0,0,0};

	srand(time(0));

	bool success = false;
	while (!success)
	{
		row = rand() % m_board_size;
		col = rand() % m_board_size;
		direction = rand() % 4;

		if (shipFits(row, col, direction, ship_size)) {
			// if going UP or LEFT, switch start and end point of ship
			switch (direction) {
			case util::UP:
				row = row - (ship_size - 1);
				break;
			case util::LEFT:
				col = col - (ship_size - 1);
				break;
			}

			if (!shipCollision(row, col, direction, ship_size, temp_ship_tiles)) {
				success = true;
				// all tiles were free, set hasShip flag for all tiles
				for (int i = 0; i < ship_size; i++) {
					m_board_tiles[temp_ship_tiles[i]]->setHasShip(true);
				}
			}
		}
	}
}
