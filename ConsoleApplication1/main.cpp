#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
int main()
{
	ofstream out("duomenys.bin", ios::binary);
	ListHeader header;
	header.count = 3;
	header.first = 1;
	header.last = 2;
	ListEntry<int> duomenai[4];
	
	duomenai[1].data = 5;
	duomenai[1].next = 3;
	duomenai[1].prev = 0;

	duomenai[2].data = 20;
	duomenai[2].prev = 3;
	duomenai[2].next = 0;

	duomenai[3].data = 10;
	duomenai[3].prev = 1;
	duomenai[3].next = 2;
	out.write((char*)&header, sizeof(ListHeader));
	out.write((char*)&duomenai, sizeof(ListEntry<int>) * 4);
	out.close();
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	do
	{
		cout << it.Get() << endl;
	}while(it.Next());
	system("pause");
	return 0;
}