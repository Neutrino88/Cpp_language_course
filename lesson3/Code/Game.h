#pragma once

#include <iostream>
#include <memory>

#include "Bot.h"
#include "Human.h"

struct GameCreator;

class Game{
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;

	Game(void) = default;

public:
    int start(void);

	friend GameCreator;
};

// Factory method
struct GameCreator {
	GameCreator(void)
		: game()
	{ }

	virtual Game* Create(void) = 0;
protected:
    Game game;

	void setPlayer1(Player* player1) {
		game.player1.reset(player1);
	}
	void setPlayer2(Player* player2) {
		game.player2.reset(player2);
	}
};

struct GameCreatorHumanBot : public GameCreator {
	Game* Create(void) {
		setPlayer1(new Human());
		setPlayer2(new Bot());

		return &game;
	}
};

struct GameCreatorBotHuman : public GameCreator {
	Game* Create(void) {
		setPlayer1(new Bot());
		setPlayer2(new Human());

		return &game;
	}
};

struct GameCreatorBotBot : GameCreator {
	Game* Create(void) {
		setPlayer1(new Bot());
		setPlayer2(new Bot());

		return &game;
	}
};

