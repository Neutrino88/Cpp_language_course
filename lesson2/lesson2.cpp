#include "Cbool.h"
#include "MySmartPointer.h"

void foo(MySmartPointer<Cbool> ptr) {
}


int main()
{
	MySmartPointer<Cbool> p1( new Cbool(123, 321) );

	std::cout << (*p1).sum() << "\n";
	std::cout << p1->sum() << "\n";

	foo(p1);

	MySmartPointer<Cbool> p2 = p1;

	foo(p2);

	std::cout << p1[0].sum() << "\n";

    return 0;
}

