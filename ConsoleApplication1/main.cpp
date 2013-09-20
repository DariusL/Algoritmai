#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
int main()
{
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	data.InsertAfter(it, 20);
	data.InsertAfter(it, 18);
	data.InsertAfter(it, 16);
	data.InsertAfter(it, 14);
	data.InsertAfter(it, 10);
	while (it.Next())
	{
		cout << it.Get() << endl;
	}
	it = data.End();
	it.Prev();
	it.Prev();
	it.Remove();
	cout << endl;
	it = data.Begin();
	while (it.Next())
	{
		cout << it.Get() << endl;
	}
	auto left = data.Begin();
	auto right = data.End();
	left.Next();
	right.Prev();
	data.Swap(left, right);
	cout << endl;
	it = data.Begin();
	while (it.Next())
	{
		cout << it.Get() << endl;
	}
	system("pause");
	return 0;
}