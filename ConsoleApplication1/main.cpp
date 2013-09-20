#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>
int main()
{
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(0, numeric_limits<UINT>::max() - 5);
	auto num = bind(dist, gen);
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	UINT genTime = clock();
	for(UINT i = 0; i < 1000; i++)
		data.InsertAfter(it, num());
	genTime = clock() - genTime;
	UINT readTime = clock();
	it = data.Begin();
	while(it.Next())
		it.Get();
	readTime = clock() - readTime;
	cout << "gen - " << genTime / (double)CLOCKS_PER_SEC << endl << "read - " << readTime / (double)CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;
}