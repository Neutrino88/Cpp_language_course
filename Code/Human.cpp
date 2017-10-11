#include "Human.h"

void Human::printFields(void) const {
	std::string line;
	const std::string alphabet = "     A B C D E F G H I J       A B C D E F G H I J       ";

	std::cout << std::endl;

	std::cout << alphabet << std::endl;

	for (int i = 0; i < FL_FIELD_SIZE; ++i) {
		if (i < 9)	line = " " + std::to_string(i + 1) + "  |";
		else		line = " " + std::to_string(i + 1) + " |";

		for (int j = 0; j < FL_FIELD_SIZE; ++j) {
			switch (field.f[i][j]) {
			case CELL_WATER:
				line += ". ";
				break;
			case CELL_WHOLE_SHIP:
				line += "# ";
				break;
			case CELL_WOUNDED_SHIP:
				line += "O ";
				break;
			default:
				line += "? ";
			}
		}
		
		if (i < 9)	line += "| " + std::to_string(i + 1) + "  |";
		else		line += "| " + std::to_string(i + 1) + " |";

		for (int j = 0; j < FL_FIELD_SIZE; ++j) {
			switch (enemyField.f[i][j]) {
			case CELL_WATER:
				line += ". ";
				break;
			case CELL_WHOLE_SHIP:
				line += "# ";
				break;
			case CELL_WOUNDED_SHIP:
				line += "O ";
				break;
			default:
				line += "? ";
			}
		}

		if (i < 9)	line += "| " + std::to_string(i + 1) + "   ";
		else		line += "| " + std::to_string(i + 1) + "  ";
		std::cout << line << std::endl;
	}

	std::cout << alphabet << std::endl;
};

void Human::setLastShotResult(Cell result) {
	enemyField.f[lastShot.x][lastShot.y] = result;
	printFields();
}