#pragma once 
#include "Globals.h"
#include "DataArray.h"

template <class S>
class DataHeap : public DataArray<S>
{
public:
	DataHeap(string file);
	DataHeap(DataHeap<S> &other);
	DataHeap(DataHeap<S> &&other);
	~DataHeap(){}

	void Add(const S &item);
	S Pop();

private:
	void Add(S item, UINT pos);
	void SiftDown(UINT pos, UINT count);
};

template <class S>
DataHeap<S>::DataHeap(string file) : DataArray(file, 0)
{
	ops += 1;
	WriteHeader(0);
}

template <class S>
DataHeap<S>::DataHeap(DataHeap<S> &other) : Data(forward<DataHeap<S>>(other))
{
}

template <class S>
DataHeap<S>::DataHeap(DataHeap<S> &&other) : Data(forward<DataHeap<S>>(other))
{
}

template <class S>
void DataHeap<S>::Add(const S &item)
{
	ops += 1;
	Add(item, GetCount());
}

template <class S>
void DataHeap<S>::Add(S item, UINT pos)
{
	if(pos == 0)
	{
		(*this)[pos] = item;
		ops += 1;
	}
	else
	{
		UINT parent = (pos - 1) / 2;
		S p = (*this)[parent];
		if(p < item)
		{
			(*this)[pos] = p;
			Add(item, parent);
			ops += 3;
		}
		else
		{
			(*this)[pos] = item;
			ops += 2;
		}
		ops += 4;
	}
	ops += 1;
}

template <class S>
S DataHeap<S>::Pop()
{
	UINT count = GetCount();
	S ret = (*this)[0];
	(*this)[0] = (*this)[count - 1];
	WriteHeader(count - 1);
	SiftDown(0, count);
	ops += 6;
	return ret;
}

template <class S>
void DataHeap<S>::SiftDown(UINT pos, UINT count)
{
	UINT child = pos * 2 + 1;
	UINT swap = pos;
	if(child < count)
		if((*this)[swap] < (*this)[child])
			swap = child;
	if(child + 1 < count)
		if((*this)[swap] < (*this)[child + 1])
			swap = child + 1;
	ops += 12;
	if(swap != pos)
	{
		Swap(swap, pos);
		SiftDown(swap, count);
		ops += 2;
	}
	else
	{
		return;
	}
}