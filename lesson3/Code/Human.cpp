#include "Human.h"

Human::Human(void)
    : Player()
{ }

void Human::printFields(void) const {
    std::string line;
    const std::string alphabet = "     A B C D E F G H I J       A B C D E F G H I J       ";

    std::cout << std::endl;

    std::cout << alphabet << std::endl;

    for (int i = 0; i < FL_FIELD_SIZE; ++i) {
        if (i < 9)  line = " " + std::to_string(i + 1) + "  |";
        else        line = " " + std::to_string(i + 1) + " |";

        for (int j = 0; j < FL_FIELD_SIZE; ++j) {
            switch (field.f[i][j]) {
            case CELL_WATER:
                line += ". ";
                break; 
            case CELL_WHOLE_SHIP:
                line += "# ";
                break;
            case CELL_WOUNDED_SHIP:
                line += "• ";
                break;
            default:
                line += ". ";
            }
        }
        
        if (i < 9)  line += "| " + std::to_string(i + 1) + "  |";
        else        line += "| " + std::to_string(i + 1) + " |";

        for (int j = 0; j < FL_FIELD_SIZE; ++j) {
            switch (enemyField.f[i][j]) {
            case CELL_WATER:
                line += "O ";
                break;
            case CELL_WHOLE_SHIP:
                line += "# ";
                break;
            case CELL_WOUNDED_SHIP:
                line += "• ";
                break;
            default:
                line += ". ";
            }
        }

        if (i < 9)  line += "| " + std::to_string(i + 1) + "   ";
        else        line += "| " + std::to_string(i + 1) + "  ";
        std::cout << line << std::endl;
    }

    std::cout << alphabet << std::endl;
};

Cell Human::doShot(void) {
    printFields();

    std::regex regexShot("^[A-J]([1-9]|(10))$");
    std::string line;

    std::cout << "Do shot: ";

    do {
        std::cin >> line;

        if (std::regex_match(line, regexShot)) break;

        std::cout << "Uncorrect cell number!" << std::endl << "Repeat please: ";
    } while (true);
    
    lastShot.y = line[0] - 'A';
    lastShot.x = (line[1] - '0') - 1;
    
    if (line.length() > 2)
        lastShot.x = (lastShot.x + 1) * 10 + (line[2] - '0') - 1;

    return lastShot;
}
