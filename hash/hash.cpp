#include "hash.h"
template<class X> int divMethod(X& key, int size)
{
	return key % size;
}
int main()
{
	int x[6] = { 33, 10, 44, 80, 30, 50	};
	for (int i = 0; i < 6; std::cout << x[i]<<" ", i++);
	std::cout << std::endl;
	Hash<int> testhash(divMethod, 7);
	std::cout << testhash << '\n';

	for (int i = 0; i < 6; testhash.Add(x[i]), i++);
	std::cout << testhash << '\n';
	std::cout << "Test - find where x[2]:" ;
	std::cout << testhash.Find(x[2]) << "\n";
	std::cout << "Test - delete x[4]:\n";
	testhash.Delete(x[4]);
	std::cout << testhash << '\n';
	std::cout << "Test - clear:\n";
	testhash.Clear();
	std::cout << testhash << '\n';
	return 0;
}