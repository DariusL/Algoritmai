#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>

#include "Merge.h"


int main()
{
	default_random_engine gen;
	//uniform_int_distribution<UINT> dist(1, numeric_limits<UINT>::max());
	uniform_int_distribution<UINT> dist(1, 30);
	auto num = bind(dist, gen);
	UINT count = 5;

	DataArray<UINT> one("one", 5);
	for(UINT i = 0; i < count; i++)
	{
		one[i] = num();
	}
	one.Print();
	for(UINT i = 0; i < count; i++)
	{
		one[i] = one[0];
	}
	one.Print();
	system("pause");
	return 0;
}

