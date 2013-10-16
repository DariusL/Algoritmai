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
	static const int OPEN_FLAGS = ios::binary | ios::in | ios::out | ios::trunc;
public:
	Data(string file);
	Data(Data<H, S> &&other);
	Data(Data<H, S> &other);
	Data<H, S> &operator=(Data<H, S> &other);
	virtual ~Data();
	void Delete();
	UINT SegmentCount();

	virtual bool IsSorted() = 0;
	virtual void Print() = 0;
protected:
	S Read(UINT pos);
	void Write(const S &what, UINT pos);
	H ReadHeader();
	void WriteHeader(const H &header);

	void BaseClear();
};

template <class H, class S>
Data<H, S>::Data(string file) : data(file, OPEN_FLAGS)
{
	hSize = sizeof(H);
	sSize = sizeof(S);
	this->file = file;
	ops += 4;
}


template <class H, class S>
Data<H, S>::~Data()
{
	if(file != "")
	{
		data.close();
		Delete();
		ops += 2;
	}
	ops += 2;
}

template <class H, class S>
Data<H, S>::Data(Data<H, S> &&other)
{
	data = move(other.data);
	file = other.file;
	hSize = other.hSize;
	sSize = other.sSize;
	other.file = "";
	ops += 5;
}

template <class H, class S>
Data<H, S>::Data(Data<H, S> &other)
{
	file = other.file + " copy";
	hSize = other.hSize;
	sSize = other.sSize;
	data = fstream(file, OPEN_FLAGS);
	H header = other.ReadHeader();
	S segment;
	data.write((char*)&header, hSize);
	UINT count = other.SegmentCount();
	ops += 7;
	for(UINT i = 0; i < count; i++)
	{
		segment = other.Read(i);
		data.write((char*)&segment, sSize);
		ops += 1;
	}
}

template <class H, class S>
Data<H, S> &Data<H, S>::operator=(Data<H, S> &other)
{
	if(this != &other)
	{
		data.close();
		Delete();
		file = other.file + " copy";
		data = fstream(file, OPEN_FLAGS);
		WriteHeader(other.ReadHeader());
		S segment;
		UINT count = other.SegmentCount();
		ops += 7;
		for(UINT i = 0; i < count; i++)
		{
			segment = other.Read(i);
			data.write((char*)&segment, sSize);
			ops += 2;
		}
	}
	return *this;
}

template <class H, class S>
S Data<H, S>::Read(UINT pos)
{
	S ret;
	if(pos < SegmentCount())
	{
		data.seekg(hSize + pos * sSize);
		data.read((char*)&ret, sSize);
		ops += 2;
	}
	ops += 2;
	return ret;
}

template <class H, class S>
void Data<H, S>::Write(const S &what, UINT pos)
{
	ops += 2;
	data.seekg(hSize + pos * sSize);
	data.write((char*)&what, sSize);
}

template <class H, class S>
H Data<H, S>::ReadHeader()
{
	ops += 4;
	H ret;
	data.seekg(0);
	data.read((char*)&ret, hSize);
	return ret;
}

template <class H, class S>
void Data<H, S>::WriteHeader(const H &header)
{
	ops += 2;
	data.seekg(0);
	data.write((char*)&header, hSize);
}

template <class H, class S>
UINT Data<H, S>::SegmentCount()
{
	ops += 3;
	data.seekg(0, ios::end);
	UINT size = data.tellg();
	return (size - hSize) / sSize;
}

template <class H, class S>
void Data<H, S>::Delete()
{
	ops += 2;
	data.close();
	remove(file.c_str());
}

template <class H, class S>
void Data<H, S>::BaseClear()
{
	ops += 2;
	data.close();
	data.open(file.c_str(), OPEN_FLAGS);
}