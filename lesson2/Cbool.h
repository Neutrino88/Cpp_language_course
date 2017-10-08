#pragma once
#include <iostream>

class Cbool {
	int a;
	int b;

public:
	Cbool(int a = 5, int b= 7): a(a),b(b) {
		std::cout << "constructor Cbool\n";
	};

	~Cbool() {
		std::cout << "destructor Cbool\n";
	};

	int sum(void) {
		return a + b;
	}

	Cbool &operator=(const Cbool &obj) {
		a = obj.a;
		b = obj.b;

		return *this;
	}
};
