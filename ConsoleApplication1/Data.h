#pragma once
#include <string>
#include <fstream>

#include "Iterator.h"
#include "ArrayAccessor.h"
using namespace std;

template <class T>
class Data
{
	friend class ArrayAcessor<T>;
protected:
	basic_fstream<T> data;
public:
	Data(string file) : data(file, ios::binary | ios::in | ios::out){}
	virtual ~Data();
protected:
	T Read(long long pos);
	void Write(T what, long long pos);
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
	data.seekg(pos);
	ret = data.peek();
	return ret;
}

template <class T>
void Data<T>::Write(T what, long long pos)
{
	data.seekg(pos);
	data.put(what);
}