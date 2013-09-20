#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
int main()
{
	ofstream out("duomenys.bin", ios::binary);
	UINT duomenai[3] = {1, 2, 20};
	DataList<UINT> data("duomenys.bin");
	system("pause");
	return 0;
}