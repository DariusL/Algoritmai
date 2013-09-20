#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
int main()
{
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(0, numeric_limits<UINT>::max() - 5);
	auto num = bind(dist, gen);
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	/*for(UINT i = 0; i < 1000000; i++)
		data.InsertAfter(it, num());*/
	it = data.Begin();
	while(it.Next())
		cout << it.Get() << endl;
	system("pause");
	return 0;
}