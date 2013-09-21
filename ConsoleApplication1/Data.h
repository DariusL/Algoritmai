#pragma once
#pragma warning(disable:4244)
#include <string>
#include <fstream>

#include "Globals.h"
using namespace std;

template <class H, class S>
class Data
{
private:
	fstream data;
	string file;
	int hSize;
	int sSize;
public:
	Data(string file);
	Data(Data<H, S> &&other);
	Data(Data<H, S> &other);
	virtual ~Data();
	void Delete();
	bool IsEmpty();
	UINT SegmentCount();
protected:
	S Read(UINT pos);
	void Write(const S &what, UINT pos);
	H ReadHeader();
	void WriteHeader(const H &header);
};

template <class H, class S>
Data<H, S>::Data(string file) : data(file, ios::binary | ios::in | ios::out)
{
	hSize = sizeof(H);
	sSize = sizeof(S);
	this->file = file;
}

template <class H, class S>
Data<H, S>::~Data()
{
	if(file != "")
	{
		data.close();
		Delete();
	}
}

template <class H, class S>
Data<H, S>::Data(Data<H, S> &&other)
{
	data = move(other.data);
	file = other.file;
	hSize = other.hSize;
	sSize = other.sSize;
	other.file = "";
}

template <class H, class S>
Data<H, S>::Data(Data<H, S> &other)
{
	file = other.file + " copy";
	hSize = other.hSize;
	sSize = other.sSize;
	data = fstream(file, ios::binary | ios::out);
	H header = other.ReadHeader();
	S segment;
	data.write((char*)&header, hSize);
	UINT count = other.SegmentCount();
	for(UINT i = 0; i < count; i++)
	{
		segment = other.Read(i);
		data.write((char*)&segment, sSize);
	}
	data.close();
	data.open(file, ios::binary | ios::in | ios::out);
}

template <class H, class S>
bool Data<H, S>::IsEmpty()
{
	data.seekg(0, ios_base::end);
	int size = data.tellg();
	return size <= 0;
}

template <class H, class S>
S Data<H, S>::Read(UINT pos)
{
	S ret;
	if(pos < SegmentCount())
	{
		data.seekg(hSize + pos * sSize);
		data.read((char*)&ret, sSize);
	}
	return ret;
}

template <class H, class S>
void Data<H, S>::Write(const S &what, UINT pos)
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
void Data<H, S>::WriteHeader(const H &header)
{
	if(!data.is_open())
	{
		data.open(file, ios::binary | ios::out);
		data.write((char*)&header, hSize);
		data.close();
		data.open(file, ios::binary | ios::in | ios::out);
	}
	else
	{
		data.seekg(0);
		data.write((char*)&header, hSize);
	}
}

template <class H, class S>
UINT Data<H, S>::SegmentCount()
{
	data.seekg(0, ios::end);
	UINT size = data.tellg();
	return (size - hSize) / sSize;
}

template <class H, class S>
void Data<H, S>::Delete()
{
	data.close();
	remove(file.c_str());
}