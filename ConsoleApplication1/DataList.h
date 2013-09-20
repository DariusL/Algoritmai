#pragma once

#include "Data.h"
#include "Iterator.h"
#include "ListEntry.h"
#include "ListHeader.h"
template <class S>
class DataList : public Data<ListHeader, ListEntry<S>>
{
	friend class Iterator<S>;
public:
	DataList(string file) : Data(file){}
	~DataList(){}

	Iterator<S> Begin();
	void Remove(Iterator<S> it);
	bool Valid(Iterator<S> it);
private:
	bool Valid(UINT pos);
};

template <class S>
Iterator<S> DataList<S>::Begin()
{
	ListHeader header = ReadHeader();
	return Iterator<S>(this, header.first);
}

template <class S>
void DataList<S>::Remove(Iterator<S> it)
{
	if(Valid(it))
	{
		ListHeader h = ReadHeader();
		h.count--;
		WriteHeader(h);
		ListEntry<S> e = Read(it.entry);
		e.prev = 0;
		e.next = 0;
		Write(e, it.entry);
	}
}

template <class S>
bool DataList<S>::Valid(Iterator<S> it)
{
	return Valid(it.entry);
}

template <class S>
bool DataList<S>::Valid(UINT pos)
{
	ListHeader h = ReadHeader();
	return pos != h.first && pos != h.last && pos != 0;
}