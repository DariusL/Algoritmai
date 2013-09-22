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
	uniform_int_distribution<UINT> dist(1, numeric_limits<UINT>::max());
	auto num = bind(dist, gen);
	UINT count = 5000;
	system("pause");
	return 0;
}

