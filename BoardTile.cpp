#include "pch.h"
#include "BoardTile.h"

BoardTile::BoardTile() {
	m_bombed = false;
	m_has_ship = false;
}

bool BoardTile::isBombed() {
	return m_bombed;
}

void BoardTile::setBombed(bool bombed) {
	m_bombed = bombed;
}

bool BoardTile::hasShip() {
	return m_has_ship;
}

void BoardTile::setHasShip(bool has_ship) {
	m_has_ship = has_ship;
}

