#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <fstream>
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
	UINT counts[] = {10, 50, 100, 500, 1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	bool sorted;
	ofstream out("rez.csv", ios::trunc);
	for(UINT count : counts)
	{
		ops = 0;
		auto stuff = GetRandomArray("gfasgasg", 0, numeric_limits<UINT>::max(), count);
		time = clock();
		RadixSort(stuff);
		time = clock() - time;
		sorted = stuff.IsSorted();
		cout << "sorted " << sorted << " count " << count << " time " << time << " ops " << ops << endl;
		out << count << ';' << time << ';' << ops << ";\n";
	}
	out.close();
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