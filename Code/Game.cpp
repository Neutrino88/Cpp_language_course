#include "Game.h"

Game::Game(Player* player1, Player * player2) 
    : player1(player1)
    , player2(player2)
{ }

int Game::start(void) {
    Cell shot;
    ShotResult shotResult;
    bool shotFirstPl = false;

    int ships1 = 10;
    int ships2 = 10;

    do {
        shotFirstPl = !shotFirstPl;
        do {
            std::cout << player1->getName() + ": " << std::endl;
            
            shot = player1->doShot();
            shotResult = player2->getShot(shot);
            player1->setLastShotResult(shotResult);

            if (shotFirstPl && shotResult == SHOTR_KILLED) {
                --ships1;
            }
            if (!shotFirstPl && shotResult == SHOTR_KILLED) {
                --ships2;
            }

            std::cout << "[" << static_cast<char>('A' + shot.y) << shot.x + 1 << "] - ";
            std::cout << (shotResult == SHOTR_KILLED ? "KILL" : (shotResult == SHOTR_WOUNDED ? "WOUNDED" : "MISSED")) << std::endl;
        } while (ships1 > 0 && ships2 > 0 && (shotResult == CELL_WOUNDED_SHIP || shotResult == CELL_WHOLE_SHIP));

        // swap players
        Player* buff = player1;
        player1 = player2;
        player2 = buff;
    } while (ships1 > 0 && ships2 > 0);

    if (!shotFirstPl)
        std::cout << player1->getName() << " won!" << std::endl;
    else
        std::cout << player2->getName() << " won!" << std::endl;

    return 0;
}
