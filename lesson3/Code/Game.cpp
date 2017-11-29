#include "Game.h"

int Game::start(void) {
    Cell shot;
    ShotResult shotResult;
    bool shotFirstPl = false;

    do {
        shotFirstPl = !shotFirstPl;
        do {
            std::cout << (shotFirstPl ? "Player 1:" : "Player 2:" ) << std::endl;
            
            shot = player1->doShot();
            shotResult = player2->getShot(shot);
            player1->setLastShotResult(shotResult);
			
            std::cout << "[" << static_cast<char>('A' + shot.y) << shot.x + 1 << "] - ";
            std::cout << (shotResult == SHOTR_KILLED ? "KILL" : (shotResult == SHOTR_WOUNDED ? "WOUND" : (shotResult == SHOTR_MISSED ? "MISS" : "LOSE"))) << std::endl;
        } while (shotResult == SHOTR_WOUNDED || shotResult == SHOTR_KILLED);

        // swap players
		std::swap(player1, player2);
    } while (shotResult != SHOTR_LOSED);

    return 0;
}
