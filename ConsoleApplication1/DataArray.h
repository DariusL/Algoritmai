#pragma once
#include "data.h"
#include "ArrayAccessor.h"
template <class S>
class DataArray : public Data<UINT, S>
{
	friend class ArrayAcessor<S>;
public:
	DataArray(string file, UINT size);
	~DataArray(){}
	DataArray(DataArray<S> &&other);
	UINT GetCount();
	bool IsSorted();
	void Print();
	void Swap(UINT a, UINT b);
	void PushBack(S &item);
	void Clear();

	ArrayAcessor<S> operator[](UINT pos);
};

template <class S>
ArrayAcessor<S> DataArray<S>::operator[](UINT pos)
{
	UINT count = ReadHeader();
	if(pos >= count)
	{
		count = pos + 1;
		WriteHeader(count);
		ops += 2;
	}
	ops += 3;
	return ArrayAcessor<S>(this, pos);
}

template <class S>
DataArray<S>::DataArray(string file, UINT size) : Data(file)
{
	WriteHeader(size);
	ops += 1;
}

template <class S>
DataArray<S>::DataArray(DataArray<S> &&other) : Data(forward<DataArray<S>>(other))
{
}

template <class S>
UINT DataArray<S>::GetCount()
{
	ops += 1;
	return ReadHeader();
}

template <class S>
bool DataArray<S>::IsSorted()
{
	UINT count = GetCount();
	for(UINT i = 0; i < count - 1; i++)
	{
		ops += 1;
		if(Read(i) > Read(i+1))
			return false;
	}
	ops += 2;
	return true;
}

template <class S>
void DataArray<S>::Print()
{
	UINT count = GetCount();
	for(UINT i = 0; i < count; i++)
	{
		cout << Read(i) << endl;
		ops += 2;
	}
	ops += 2;
	cout << endl;
}

template <class S>
void DataArray<S>::Swap(UINT a, UINT b)
{
	UINT count = GetCount();
	S temp = Read(a);
	Write(Read(b), a);
	Write(temp, b);
	ops += 4;
}

template <class S>
void DataArray<S>::PushBack(S &item)
{
	ops += 2;
	(*this)[ReadHeader()] = item;
}

template <class S>
void DataArray<S>::Clear()
{
	ops += 1;
	WriteHeader(0);
}