#pragma once
#include <string>
#include <fstream>

#include "Globals.h"
using namespace std;

template <class H, class S>
class Data
{
private:
	fstream data;
	int hSize;
	int sSize;
public:
	Data(string file);
	virtual ~Data();
protected:
	S Read(UINT pos);
	void Write(S what, UINT pos);
	H ReadHeader();
	void WriteHeader(H header);
};

template <class H, class S>
Data<H, S>::Data(string file) : data(file, ios::binary | ios::in | ios::out)
{
	hSize = sizeof(H);
	sSize = sizeof(S);
}

template <class H, class S>
Data<H, S>::~Data()
{
	data.close();
}

template <class H, class S>
S Data<H, S>::Read(UINT pos)
{
	S ret;
	data.seekg(hSize + pos * sSize);
	data.read((char*)&ret, sSize);
	return ret;
}

template <class H, class S>
void Data<H, S>::Write(S what, UINT pos)
{
	data.seekg(hSize + pos * sSize);
	data.write((char*)&what, sSize);
}

template <class H, class S>
H Data<H, S>::ReadHeader()
{
	H ret;
	data.seekg(0);
	data.read((char*)&ret, hSize);
	return ret;
}

template <class H, class S>
void Data<H, S>::WriteHeader(H header)
{
	data.seekg(0);
	data.write((char*)&header, hSize);
}