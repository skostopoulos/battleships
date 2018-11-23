#pragma once
#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <unordered_map>

namespace util {

	static const int default_board_size = 10;

	enum DifficultyLevel
	{
		EASY = 1, MEDIUM = 2, HARD = 3
	};

	static const DifficultyLevel default_difficulty_level = MEDIUM;

	enum ShipType
	{
		CARRIER, DESTROYER, BATTLESHIP
	};

	static const ShipType default_ship_type = DESTROYER;
	
	struct Fleet
	{
		int num_of_carriers;
		int num_of_destroyers;
		int num_of_battleships;
	};

	const Fleet easy_level_fleet   = { 1, 2, 2 };
	const Fleet medium_level_fleet = { 0, 2, 1 };
	const Fleet hard_level_fleet   = { 3, 2, 1 };
	
	enum Direction
	{
		UP, DOWN, LEFT, RIGHT
	};

	int   difficultyToBoardSize(DifficultyLevel level);
	int   difficultyToShipNum(DifficultyLevel level);
	Fleet difficultyLevelToFleet(DifficultyLevel level);
	int   shipTypeToShipSize(ShipType ship_type);
	int   convertCharRowtoInt(char row);

}

#endif _UTILITIES_H