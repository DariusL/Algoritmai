#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
int main()
{
	ofstream out("duomenys.bin", ios::binary);
	ListHeader header;
	header.count = 1;
	header.first = 1;
	header.last = 2;
	ListEntry<int> duomenai[4];
	
	duomenai[1].data = 0;
	duomenai[1].next = 3;
	duomenai[1].prev = 0;

	duomenai[2].data = 0;
	duomenai[2].prev = 3;
	duomenai[2].next = 0;

	duomenai[3].data = 3;
	duomenai[3].prev = 1;
	duomenai[3].next = 2;
	out.write((char*)&header, sizeof(ListHeader));
	out.write((char*)&duomenai, sizeof(ListEntry<int>) * 4);
	out.close();
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	while (it.Next())
	{
		cout << it.Get() << endl;
	}
	system("pause");
	return 0;
}