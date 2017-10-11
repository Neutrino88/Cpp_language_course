#include "Game.h"

int main(void) {
	Bot player2("I am bot-winner!");
	Human player1("I am human-winner!");

	Game game(player1, player2);
	game.start();

	return 0;
}