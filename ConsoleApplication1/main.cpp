#include "DataArray.h"
int main()
{
	basic_ofstream<int> out("duomenys.txt", ios::binary);
	int duomenai[3] = {1, 2, 3};
	out.write(duomenai, 3);
	out.close();
	DataArray<int> data("duomenys.txt");
	int safas = data[1];
	return 0;
}