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
	auto arr = GetRandomArray("tmp", 1, numeric_limits<UINT>::max(), 5000);
	bool init = arr.IsSorted();
	UINT time = clock();
	HeapSort<UINT>(arr);
	time = clock() - time;
	bool sorted = arr.IsSorted();
	cout << "Array of 5000, heap\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	auto lst = GetRandomList("tmp", 1, numeric_limits<UINT>::max(), 5000);
	init = lst.IsSorted();
	time = clock();
	HeapSort(lst);
	time = clock() - time;
	sorted = lst.IsSorted();
	cout << "List of 5000, heap\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	arr = GetRandomArray("tmp", 1, numeric_limits<UINT>::max(), 5000);
	init = arr.IsSorted();
	time = clock();
	RadixSort(arr);
	time = clock() - time;
	sorted = arr.IsSorted();
	cout << "Array of 5000, radix\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	lst = GetRandomList("tmp", 1, numeric_limits<UINT>::max(), 5000);
	init = lst.IsSorted();
	time = clock();
	RadixSort(lst);
	time = clock() - time;
	sorted = lst.IsSorted();
	cout << "List of 5000, radix\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	arr = GetRandomArray("tmp", 1, numeric_limits<UINT>::max(), 5000);
	init = arr.IsSorted();
	time = clock();
	arr = MergeSort(arr);
	time = clock() - time;
	sorted = arr.IsSorted();
	cout << "Array of 5000, merge\n";
	cout << "Initially sorted " << init << endl;
	cout << "Sorted " << sorted << endl;
	cout << "Sort time " << time / (double)CLOCKS_PER_SEC << " seconds\n\n";

	lst = GetRandomList("tmp", 1, numeric_limits<UINT>::max(), 5000);
	init = lst.IsSorted();
	time = clock();
	lst = MergeSort(lst);
	time = clock() - time;
	sorted = lst.IsSorted();
	cout << "List of 5000, merge\n";
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