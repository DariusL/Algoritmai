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
	auto array = GetRandomArray("heap array", 1, numeric_limits<UINT>::max(), 5000);
	bool init = array.IsSorted();
	UINT time = clock();
	HeapSort<UINT>(array);
	time = clock() - time;
	bool sorted = array.IsSorted();
	cout << "Array of 5000, heap\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	auto list = GetRandomList("heap list", 1, numeric_limits<UINT>::max(), 5000);
	init = list.IsSorted();
	time = clock();
	HeapSort(list);
	time = clock() - time;
	sorted = list.IsSorted();
	cout << "List of 5000, heap\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	auto rarray = GetRandomArray("radix array", 1, numeric_limits<UINT>::max(), 5000);
	init = rarray.IsSorted();
	time = clock();
	RadixSort(rarray);
	time = clock() - time;
	sorted = rarray.IsSorted();
	cout << "Array of 5000, radix\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	auto rlist = GetRandomList("radix list", 1, numeric_limits<UINT>::max(), 5000);
	init = rlist.IsSorted();
	time = clock();
	RadixSort(rlist);
	time = clock() - time;
	sorted = rlist.IsSorted();
	cout << "Array of 5000, radix\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

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