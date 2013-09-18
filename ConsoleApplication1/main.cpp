#include "DataArray.h"
#include <numeric>
int main()
{
	basic_ofstream<int> out("duomenys.txt", ios::binary);
	int duomenai[3] = {1, 2, 20};
	out.write(duomenai, 3);
	out.close();
	DataArray<int> data("duomenys.txt");
	int safas = data[2];
	return 0;
}