#include "pch.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

int main() {

	while(1) {
		GameManager gameManager;
		gameManager.initGame();
		gameManager.playGame();
		if (!gameManager.restartGame()) {
			break;
		}
	}
	
	return 0;

}