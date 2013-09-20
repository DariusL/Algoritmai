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
};

template <class S>
Iterator<S> DataList<S>::Begin()
{
	ListHeader header = ReadHeader();
	return Iterator<S>(this, header.first);
}