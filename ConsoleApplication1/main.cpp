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
	/*DataList<UINT> data("input");
	auto it = data.Begin();
	UINT genTime = clock();
	for(UINT i = 0; i < count; i++)
		data.InsertAfter(it, num());
	
	genTime = clock() - genTime;
	UINT sortTime = clock();
	data = Merge<UINT>(data);
	sortTime = clock() - sortTime;
	UINT checkTime = clock();
	bool isSorted = data.IsSorted();
	checkTime = clock() - sortTime;
	cout << "sorting " << count << " item list" << endl;
	cout << (isSorted ? "sorted" : "not sorted") << endl;
	cout << "gen time " << genTime / (double)CLOCKS_PER_SEC << endl;
	cout << "sort time " << sortTime / (double)CLOCKS_PER_SEC << endl;
	cout << "check time " << checkTime / (double)CLOCKS_PER_SEC << endl;*/

	DataArray<UINT> arrayData("input", count);
	for(UINT i = 0; i < count; i++)
		arrayData[i] = num();
	system("pause");
	return 0;
}

