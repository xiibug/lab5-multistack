#include <iostream>
#include "Multistack.h"

int main()
{
	TMultiStack<int> b(9, 3);
	b.Push(1, 0);
	b.Push(1, 1);
	b.Push(1, 1);
	b.Push(1, 1);

	b.Push(3, 1);
	cout << b;
  return 0;
}
