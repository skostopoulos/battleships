#pragma once

#include "pch.h"
#include <vector>
#include "BoardTile.h"


class Board {
public:
	Board();
	Board(int board_size);
	~Board();

	bool isBombed(int tile_id);
	void setBombed(int tile_id);

	bool hasShip(int tile_id);
	void setHasShip(int tile_id);
	

private:
	int m_board_size;
	std::vector<BoardTile*> m_board_tiles;

};