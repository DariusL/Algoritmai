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

private:
	void Add(S item, UINT pos);
};

template <class S>
DataHeap<S>::DataHeap(string file) : DataArray(file, 0)
{
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
	Add(item, SegmentCount());
}

template <class S>
void DataHeap<S>::Add(S item, UINT pos)
{
	if(pos == 0)
	{
		(*this)[pos] = item;
	}
	else
	{
		UINT parent = (pos - 1) / 2;
		S p = (*this)[parent];
		if(p < item)
		{
			(*this)[pos] = p;
			Add(item, parent);
		}
		else
		{
			(*this)[pos] = item;
		}
	}
}