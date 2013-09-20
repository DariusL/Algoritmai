#include "DataArray.h"
#include <numeric>
#include <iostream>
int main()
{
	ofstream out("duomenys.bin", ios::binary);
	UINT duomenai[3] = {1, 2, 20};
	UINT count = 3;
	out.write((char*)&count, sizeof(UINT));
	out.write((char*)&duomenai, sizeof(UINT) * count);
	out.close();
	DataArray<int> data("duomenys.bin");
	count = data.GetCount();
	for(int i = 0; i < count; i++)
		cout << data[i] << endl;
	system("pause");
	return 0;
}