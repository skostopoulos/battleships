#include "pch.h"
#include "BoardTile.h"
#include "Board.h"
#include "BattleshipUtilities.h"



Board::Board() {
	m_board_size = util::default_board_size;
}
Board::Board(int board_size) {
	m_board_size = board_size;
	for (int i = 0; i < m_board_size*m_board_size; i++) {
		BoardTile* board_tile = new BoardTile();
		m_board_tiles.push_back(board_tile);
	}
}

Board::~Board() {
	// Delete all board tiles
	for (size_t i = 0; i < m_board_tiles.size(); i++) {
		delete m_board_tiles[i];
	}
	m_board_tiles.clear();
}

bool Board::isBombed(int tile_id) {
	return m_board_tiles[tile_id]->isBombed();
}

void Board::setBombed(int tile_id) {
	m_board_tiles[tile_id]->setBombed(true);
}

bool Board::hasShip(int tile_id) {
	return m_board_tiles[tile_id]->hasShip();
}

void Board::setHasShip(int tile_id) {
	m_board_tiles[tile_id]->setHasShip(true);
}