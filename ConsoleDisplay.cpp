#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "ConsoleDisplay.h"
#include "BattleshipUtilities.h"

using namespace std;

ConsoleDisplay::ConsoleDisplay() {
	m_board_size = util::default_board_size;
	m_fleet = util::medium_level_fleet;
	m_message = "\n";
	m_game = NULL;
	calculateRowsForDisplayBoard();
}

ConsoleDisplay::ConsoleDisplay(util::DifficultyLevel level, Game *game) {
	m_board_size = util::difficultyToBoardSize(level);
	m_fleet = util::difficultyLevelToFleet(level);
	m_message = "   \n";
	m_game = game;
	calculateRowsForDisplayBoard();
}


void ConsoleDisplay::greetUser() {
	

	char username[100];

	cout << "################################################################################" << endl;
	cout << "#                                                                              #" << endl;
	cout << "# ##   ##  ######  ##       ####    ####   ##   ##  ######      ######  ####   #" << endl;
	cout << "# ##   ##  ##      ##      ##  ##  ##  ##  ### ###  ##            ##   ##  ##  #" << endl;
	cout << "# ## # ##  ####    ##      ##      ##  ##  ## # ##  ####          ##   ##  ##  #" << endl;
	cout << "# #######  ##      ##      ##  ##  ##  ##  ##   ##  ##            ##   ##  ##  #" << endl;
	cout << "#  ## ##   ######  ######   ####    ####   ##   ##  ######        ##    ####   #" << endl;
	cout << "#                                                                              #" << endl;
	cout << "# #####   ####  ###### ###### ##     ######  ####  ##  ## ###### #####   ####  #" << endl;
	cout << "# ##  ## ##  ##   ##     ##   ##     ##     ##     ##  ##   ##   ##  ## ##     #" << endl;
	cout << "# #####  ######   ##     ##   ##     ####    ####  ######   ##   #####   ####  #" << endl;
	cout << "# ##  ## ##  ##   ##     ##   ##     ##         ## ##  ##   ##   ##         ## #" << endl;
	cout << "# #####  ##  ##   ##     ##   ###### ######  ####  ##  ## ###### ##      ####  #" << endl;
	cout << "#                                                                              #" << endl;
	cout << "################################################################################" << endl;

	cout << endl << endl << endl;
	cout << "              Please enter your name: ";
	do {
		cin >> username;
	} while (cin.fail());
	cout << endl;
	cout << "Hi " << username << ", nice to see you. Let's begin!" << endl << endl;
}

void ConsoleDisplay::printDifficultyLevelOptions() {
	cout << "              Please select a difficulty level:" << endl;
	cout << "    --------------       --------------       --------------   " << endl;
	cout << "   |   EASY = 1   |     |  MEDIUM = 2  |     |   HARD = 3   |  " << endl;
	cout << "    --------------       --------------       --------------   " << endl;
}


void ConsoleDisplay::displayBoard() {

	string col_separator = " | ";

	cout << m_first_row << m_second_row;
	for (int row = 0; row < m_board_size; row++) {
		printRowName(row);
		for (int col = 0; col < m_board_size; col++) {
			cout << col_separator;
			int tile_id = row * m_board_size + col;
			printTile(tile_id);
		}
		cout << col_separator << endl;
		if (row != m_board_size - 1) {
			cout << m_row_separator;
		}
	}
	cout << m_second_row << "\n";
	printFleet();
}

void ConsoleDisplay::clearScreen() {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void ConsoleDisplay::saveMessageFromPreviousMove(string output_message) {
	m_message = output_message;
}

void ConsoleDisplay::printSavedMessage() {
	cout << m_message;
}

void ConsoleDisplay::printWrongInputMessage() {
	cout << "Incorrect input! Hit a cell by using the following format: ";
	cout << "Row Column       -->      eg. A1, A2, A3, ..., J10" << endl;
}

void ConsoleDisplay::printWinMessage() {

	clearScreen();
	cout << "__     ______  _    _     __           _______ _   _     _   _   _	  " << endl;
	cout << "\\ \\   / / __ \\| |  | |    \\ \\         / /_   _| \\ | |   | | | | | |  " << endl;
	cout << " \\ \\_/ / |  | | |  | |     \\ \\  / \\  / /  | | |  \\| |   | | | | | |  " << endl;
	cout << "  \\   /| |  | | |  | |      \\ \\/   \\/ /   | | | . ` |   | | | | | |  " << endl;
	cout << "   | | | |__| | |__| |       \\  / \\  /   _| |_| |\\  |   |_| |_| |_|  " << endl;
	cout << "   |_|  \\____/ \\____/         \\/   \\/   |_____|_| \\_|   (_) (_) (_)  " << endl << endl << endl;

	cout << "________________________________________________________________" << endl;
	cout << "                      _____                ______               " << endl;
	cout << "                      ___                   ____                " << endl;
	cout << "                      __          ****       __                 " << endl;
	cout << "                      _          ***         _                  " << endl;
	cout << "                    __| |__     **        __| |__               " << endl;
	cout << "                _  | o _ o |  _*     _   | o   o |              " << endl;
	cout << "           ____| |_|__| |__|_| |____| |__|_______|__            " << endl;
	cout << "          \\    | |  O | |  O | |  O | |  O    O    /           " << endl;
	cout << "         __\\___| |____| |____| |____| |____       /            " << endl;
	cout << "        \\                                 /      /             " << endl;
	cout << "         \\     O     O     O     O       /______/              " << endl;
	cout << "          \\_____________________________/                      " << endl;
	cout << "________________________________________________________________" << endl << endl << endl;

	cout << "           Thanks for playing!\n\n";
	cout << " Congratulations! You managed to sink ALL ships in " << m_game->getTotalNumOfMoves() << " moves!\n\n";
}

void ConsoleDisplay::printTile(int tile_id){

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int red = 12;
	int blue = 9;
	int white = 15;

	BoardTile* boardtile = m_game->getBoardTile(tile_id);

	if (boardtile->isBombed()) {
		if (boardtile->hasShip()){
			SetConsoleTextAttribute(hConsole, red);
			cout << "x";
		}
		else {
			SetConsoleTextAttribute(hConsole, blue);
			cout << "o";
		}
	}
	else {
		cout << " ";
	}
	SetConsoleTextAttribute(hConsole, white);
}

void ConsoleDisplay::printRowName(int col) {
	switch (col) {
	case 0: cout << "A "; break;
	case 1: cout << "B "; break;
	case 2: cout << "C "; break;
	case 3: cout << "D "; break;
	case 4: cout << "E "; break;
	case 5: cout << "F "; break;
	case 6: cout << "G "; break;
	case 7: cout << "H "; break;
	case 8: cout << "I "; break;
	case 9: cout << "J "; break;
	case 10: cout << "K "; break;
	case 11: cout << "L "; break;
	case 12: cout << "M "; break;
	case 13: cout << "N "; break;
	case 14: cout << "O "; break;
	case 15: cout << "P "; break;
	case 16: cout << "Q "; break;
	case 17: cout << "R "; break;
	case 18: cout << "S "; break;
	case 19: cout << "T "; break;
	}
}


// Private functions

void ConsoleDisplay::calculateRowsForDisplayBoard() {
	// Based on difficulty level, display board 8x8, 10x10 or 20x20
	string end_line = "\n";

	m_first_row = "     ";
	m_second_row = "    ";
	m_row_separator = "   ";

	for (int i = 0; i < m_board_size; i++) {
		if (i < 10) {
			m_first_row = m_first_row + to_string(i + 1) + "   ";
		}
		else {
			m_first_row = m_first_row + to_string(i + 1) + "  ";
		}
		m_second_row = m_second_row + "--- ";
		m_row_separator = m_row_separator + "|---";
	}
	m_first_row = m_first_row + end_line;
	m_second_row = m_second_row + end_line;
	m_row_separator = m_row_separator + "|" + end_line;
}

void ConsoleDisplay::printFleet() {
	cout << "  This is the fleet you are trying to sink:\n";
	cout << "   [ " << m_fleet.num_of_carriers << " CARRIERS, "
		<< m_fleet.num_of_destroyers << " DESTROYERS, "
		<< m_fleet.num_of_battleships << " BATTLESHIPS ]\n\n";
}
