#pragma once
#include "data.h"
#include "ArrayAccessor.h"
template <class T>
class DataArray : public Data<T>
{
	friend class ArrayAcessor<T>;
public:
	DataArray(string file) : Data(file){}
	~DataArray(){}

	ArrayAcessor<T> operator[](long long pos);
};

template <class T>
ArrayAcessor<T> DataArray<T>::operator[](long long pos)
{
	return ArrayAcessor<T>(this, pos);
}