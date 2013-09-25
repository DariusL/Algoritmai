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
	}
	return ArrayAcessor<S>(this, pos);
}

template <class S>
DataArray<S>::DataArray(string file, UINT size) : Data(file)
{
	WriteHeader(size);
}

template <class S>
DataArray<S>::DataArray(DataArray<S> &&other) : Data(forward<DataArray<S>>(other))
{
}

template <class S>
UINT DataArray<S>::GetCount()
{
	return ReadHeader();
}

template <class S>
bool DataArray<S>::IsSorted()
{
	UINT count = GetCount();
	for(UINT i = 0; i < count - 1; i++)
	{
		if(Read(i) > Read(i+1))
			return false;
	}
	return true;
}

template <class S>
void DataArray<S>::Print()
{
	UINT count = GetCount();
	for(UINT i = 0; i < count; i++)
	{
		cout << Read(i) << endl;
	}
	cout << endl;
}

template <class S>
void DataArray<S>::Swap(UINT a, UINT b)
{
	UINT count = GetCount();
	S temp = Read(a);
	Write(Read(b), a);
	Write(temp, b);
}