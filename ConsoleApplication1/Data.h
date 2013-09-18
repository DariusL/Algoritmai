#pragma once
#include <string>
#include <fstream>
using namespace std;

template <class T>
class Data
{
private:
	fstream data;
	int tSize;
public:
	Data(string file) : data(file, ios::binary | ios::in | ios::out){tSize = sizeof(T);}
	virtual ~Data();
protected:
	T Read(long long pos);
	void Write(T what, long long pos);
	bool Valid(long long pos);
};

template <class T>
Data<T>::~Data()
{
	data.close();
}

template <class T>
T Data<T>::Read(long long pos)
{
	T ret;
	data.seekg(pos * tSize);
	data.read((char*)&ret, tSize);
	return ret;
}

template <class T>
void Data<T>::Write(T what, long long pos)
{
	data.seekg(pos * tSize);
	data.write((char*)&what, tSize);
}

template <class T>
bool Valid(long long pos)
{
	data.seekg(0, stream.end);
	int size = data.tellg();
	return pos >= 0 && pos <= size;
}