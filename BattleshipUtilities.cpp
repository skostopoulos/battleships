#include "pch.h"
#include "BattleshipUtilities.h"

using namespace util;

int util::difficultyToBoardSize(DifficultyLevel level) {
	int board_size = default_board_size;
	switch (level) {
	case EASY:
	case MEDIUM:
		board_size = 10;
		break;
	case HARD:
		board_size = 20;
		break;
	}
	return board_size;
}

int util::difficultyToShipNum(DifficultyLevel level) {
	int ship_num = 3;
	switch (level) {
	case EASY:
		ship_num = 5;
		break;
	case MEDIUM:
		ship_num = 3;
		break;
	case HARD:
		ship_num = 6;
		break;
	}
	return ship_num;
}

Fleet util::difficultyLevelToFleet(DifficultyLevel level) {
	Fleet fleet = medium_level_fleet;
	switch(level) {
	case EASY:
		fleet = easy_level_fleet;
		break;
	case MEDIUM:
		fleet = medium_level_fleet;
		break;
	case HARD:
		fleet = hard_level_fleet;
		break;
	}
	return fleet;
}

int util::shipTypeToShipSize(ShipType ship_type) {
	int ship_size = 4;
	switch (ship_type) {
	case util::CARRIER:
		ship_size = 3;
		break;
	case util::DESTROYER:
		ship_size = 4;
		break;
	case util::BATTLESHIP:
		ship_size = 5;
		break;
	}
	return ship_size;
}

int util::convertCharRowtoInt(char row) {
	int retval = 0;
	switch (row) {
		case 'A': retval = 0; break;
		case 'B': retval = 1; break;
		case 'C': retval = 2; break;
		case 'D': retval = 3; break;
		case 'E': retval = 4; break;
		case 'F': retval = 5; break;
		case 'G': retval = 6; break;
		case 'H': retval = 7; break;
		case 'I': retval = 8; break;
		case 'J': retval = 9; break;
		case 'K': retval = 10; break;
		case 'L': retval = 11; break;
		case 'M': retval = 12; break;
		case 'N': retval = 13; break;
		case 'O': retval = 14; break;
		case 'P': retval = 15; break;
		case 'Q': retval = 16; break;
		case 'R': retval = 17; break;
		case 'S': retval = 18; break;
		case 'T': retval = 19; break;
	}
	return retval;
}
