#include <stdlib.h>
#include "Game.h"

std::string toCoord(Cell shot) {
    return static_cast<char>('A' + shot.y) + std::to_string(shot.x + 1);
}

ShotResult readLastShotResult(void) {
    ShotResult result;
    std::string line;

    std::cin >> line;

    if (line == "kill")         result = SHOTR_KILLED;
    else if (line == "miss")    result = SHOTR_MISSED;
    else if (line == "wound")   result = SHOTR_WOUNDED;
    else                        result = SHOTR_LOSED;

    return result;
}

Cell readShot(void) {
    std::string line;
    std::cin >> line;

    Cell shot;
    shot.y = line[0] - 'A';
    shot.x = (line[1] - '0') - 1;

    if (line.length() > 2)
        shot.x = (shot.x + 1) * 10 + (line[2] - '0') - 1;

    return shot;
}

void printShotResult(ShotResult res) {
    if (res == SHOTR_KILLED) 
        std::cout << "kill" << std::endl;
    else if (res == SHOTR_WOUNDED) 
        std::cout << "wound" << std::endl;
    else if (res == SHOTR_MISSED)
        std::cout << "miss" << std::endl;
    else
        std::cout << "lose" << std::endl;
}

int main(int argc, char** argv) {
	// Player vs Player
	if (argc == 1) {
		GameCreatorHumanBot creator;
		Game* game = creator.Create();
		game->start();
	}
	// Bot mode
	else {
		Bot bot;
		Cell shot;
		ShotResult shotResult = SHOTR_MISSED;

		bool flagDoShot = false;
		if (argc > 1 && !strcmp(argv[1], "0")) flagDoShot = true;

		while (shotResult != SHOTR_LOSED) {
			// do shot
			if (flagDoShot) {
				std::cout << toCoord(bot.doShot()) << std::endl;
				shotResult = readLastShotResult();

				if (shotResult != SHOTR_LOSED) {
					bot.setLastShotResult(shotResult);
				}
			}
			// get shot
			else {
				shot = readShot();
				shotResult = bot.getShot(shot);

				if (bot.shipsCount() == 0)
					shotResult = SHOTR_LOSED;

				printShotResult(shotResult);
			}

			if (shotResult != SHOTR_KILLED && shotResult != SHOTR_WOUNDED)
				flagDoShot = !flagDoShot;
		}
	}
    return 0;
}