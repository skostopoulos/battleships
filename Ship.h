#ifndef _SHIP_H
#define _SHIP_H
#include "BattleshipUtilities.h"

class Ship {
public:
	Ship();
	Ship(util::ShipType ship_type);

private:
	util::ShipType m_ship_type;
};

#endif _SHIP_H