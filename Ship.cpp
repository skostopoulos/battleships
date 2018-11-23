#include "pch.h"
#include "Ship.h"

Ship::Ship() {
	m_ship_type = util::default_ship_type;
}

Ship::Ship(util::ShipType ship_type) {
	m_ship_type = ship_type;
}