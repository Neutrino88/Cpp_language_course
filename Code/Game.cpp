#include "Game.h"

Game::Game(const Human & player1, const Bot & player2):
	player1(player1), player2(player2)
{ }

int Game::start(void) {
	Shot shot;
	Cell shotResult;
	int shipCount;

	bool shotFirstPl = true;
	
	do {
		do {
			std::cout << "1 player:" << std::endl;

			shotFirstPl = true;
			shot = player1.doShot();
			shipCount = player2.getShot(shot);
			player1.setLastShotResult(shot.result);

			std::cout << "[" << static_cast<char>('A' + shot.y) << shot.x+1 << "] - " << (shot.result == CELL_WOUNDED_SHIP ? "Got" : "Missed") << std::endl << shipCount << std::endl;

			char a; std::cin >> a;
		} while (shot.result == CELL_WOUNDED_SHIP);

		if (shipCount == 0) break; 

		do {
			std::cout << "2 player:" << std::endl;

			shotFirstPl = false;
			shot = player2.doShot();
			shipCount = player1.getShot(shot);
			player2.setLastShotResult(shot.result);

			std::cout << "[" << static_cast<char>('A' + shot.y) << shot.x + 1 << "] - " << (shot.result == CELL_WOUNDED_SHIP ? "Got" : "Missed") << std::endl << shipCount << std::endl;
			std::cout << shipCount << std::endl;

			char a; std::cin >> a;
		} while (shot.result == CELL_WOUNDED_SHIP);
	} while (shipCount > 0);

	if (shotFirstPl)
		std::cout << "1 player said: '" << player1.victorySpeach() << "'" << std::endl;
	else
		std::cout << "2 player said: '" << player2.victorySpeach() << "'" << std::endl;

	return 0;
}

