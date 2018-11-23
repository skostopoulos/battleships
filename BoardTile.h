#ifndef _BOARDTILE_H
#define _BOARDTILE_H

class BoardTile {
public:

	BoardTile();

	bool isBombed();
	void setBombed(bool bombed);

	bool hasShip();
	void setHasShip(bool has_ship);

private:
	bool m_bombed;
	bool m_has_ship;
};

#endif _BOARDTILE_H