#pragma once
#include "data.h"
#include "ArrayAccessor.h"
template <class S>
class DataArray : public Data<UINT, S>
{
	friend class ArrayAcessor<S>;
	UINT count;
public:
	DataArray(string file);
	~DataArray(){}
	UINT GetCount(){return count;}

	ArrayAcessor<S> operator[](UINT pos);
};

template <class S>
ArrayAcessor<S> DataArray<S>::operator[](UINT pos)
{
	return ArrayAcessor<S>(this, pos);
}

template <class S>
DataArray<S>::DataArray(string file) : Data(file)
{
	count = ReadHeader();
}