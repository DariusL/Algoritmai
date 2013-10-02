#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>

#include "MergeSort.h"
#include "HeapSort.h"
#include "RadixSort.h"

DataArray<UINT> GetRandomArray(string name, UINT from, UINT to, UINT count);
DataList<UINT> GetRandomList(string name, UINT from, UINT to, UINT count);

int main()
{
	UINT time;
	UINT count;
	count = 10;
	auto arr = GetRandomList("safas", 0, numeric_limits<UINT>::max(), count);
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	cout << count << " " << time / (double)CLOCKS_PER_SEC << endl;

	count = 100;
	arr = GetRandomList("safas", 0, numeric_limits<UINT>::max(), count);
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	cout << count << " " << time / (double)CLOCKS_PER_SEC << endl;

	count = 1000;
	arr = GetRandomList("safas", 0, numeric_limits<UINT>::max(), count);
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	cout << count << " " << time / (double)CLOCKS_PER_SEC << endl;

	count = 10000;
	arr = GetRandomList("safas", 0, numeric_limits<UINT>::max(), count);
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	cout << count << " " << time / (double)CLOCKS_PER_SEC << endl;

	count = 100000;
	arr = GetRandomList("safas", 0, numeric_limits<UINT>::max(), count);
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	cout << count << " " << time / (double)CLOCKS_PER_SEC << endl;

	system("pause");
	return 0;
}

DataArray<UINT> GetRandomArray(string name, UINT from, UINT to, UINT count)
{
	DataArray<UINT> ret(name, count);
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(from, to);
	auto num = bind(dist, gen);
	for(UINT i = 0; i < count; i++)
		ret[i] = num();
	return ret;
}

DataList<UINT> GetRandomList(string name, UINT from, UINT to, UINT count)
{
	DataList<UINT> ret(name);
	default_random_engine gen;
	uniform_int_distribution<UINT> dist(from, to);
	auto num = bind(dist, gen);
	Iterator<UINT> it = ret.Begin();
	for(UINT i = 0; i < count; i++)
		ret.InsertAfter(it, num());
	return ret;
}