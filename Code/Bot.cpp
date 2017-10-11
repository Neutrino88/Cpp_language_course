#include "Bot.h"

void Bot::getMaxEmptySqOnField(const Field & field, const Cell cell, int & resultX, int & resultY, int & resultSize) const{
	int arr[FL_FIELD_SIZE + 1][FL_FIELD_SIZE + 1];

	// Init array
	for (int h = 0; h < FL_FIELD_SIZE; ++h)
		for (int w = 0; w < FL_FIELD_SIZE; ++w) {
			if (field.f[h][w] == cell)
				arr[h][w] = 0;
			else {
				arr[h][w] = -1;
				arr[max(0, h - 1)][w] = -1;
				arr[h][max(0, w - 1)] = -1;
				arr[max(0, h - 1)][max(0, w - 1)] = -1;

				arr[min(FL_FIELD_SIZE - 1, h + 1)][w] = -1;
				arr[h][min(FL_FIELD_SIZE - 1, w + 1)] = -1;
				arr[min(FL_FIELD_SIZE - 1, h + 1)][min(FL_FIELD_SIZE - 1, w + 1)] = -1;
			}
		}

	// Fill array
	for (int h = 0; h < FL_FIELD_SIZE; ++h) {
		for (int w = 0; w < FL_FIELD_SIZE; ++w) {
			if (arr[h][w] < 0) continue;

			int a = (h > 0) ? arr[h - 1][w] : 0;
			int b = (w > 0) ? arr[h][w - 1] : 0;
			int c = (h > 0 && w > 0) ? arr[h - 1][w - 1] : 0;

			arr[h][w] = min(min(a, b), c) + 1;
		}
	}

	// search Max item
	resultSize = -1;

	for (int h = 0; h < FL_FIELD_SIZE; ++h)
		for (int w = 0; w < FL_FIELD_SIZE; ++w)
			if (arr[h][w] > resultSize) {
				resultSize = arr[h][w];
				resultX = w;
				resultY = h;
			}

	if (resultSize > -1) {
		resultX -= (resultSize - 1);
		resultY -= (resultSize - 1);
	}
}

Bot::Bot(std::string victorySpeach = "I am winner!")
	: Player(victorySpeach)
{ }

/*
void Bot::AddShips(void) {
	
}

Shot Bot::doShot(void) {
	Shot shot;



	penultimateShot = lastShot;
	lastShot = shot;

	return shot;
};

*/