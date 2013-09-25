#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>

#include "MergeSort.h"
#include "HeapSort.h"

DataArray<UINT> GetRandomArray(UINT from, UINT to, UINT count);
DataList<UINT> GetRandomList(UINT from, UINT to, UINT count);

int main()
{
	auto array = GetRandomArray(1, numeric_limits<UINT>::max(), 5000);
	bool init = array.IsSorted();
	UINT time = clock();
	HeapSort<UINT>(array);
	time = clock() - time;
	bool sorted = array.IsSorted();
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n";
	system("pause");
	return 0;
}

DataArray<UINT> GetRandomArray(UINT from, UINT to, UINT count)
{
	DataArray<UINT> ret("random array", count);
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(from, to);
	auto num = bind(dist, gen);
	for(UINT i = 0; i < count; i++)
		ret[i] = num();
	return ret;
}

DataList<UINT> GetRandomList(UINT from, UINT to, UINT count)
{
	DataList<UINT> ret("random list");
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(from, to);
	auto num = bind(dist, gen);
	Iterator<UINT> it = ret.Begin();
	for(UINT i = 0; i < count; i++)
		ret.InsertAfter(it, num());
	return ret;
}