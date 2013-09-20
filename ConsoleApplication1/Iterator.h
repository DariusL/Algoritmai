#pragma once
#include "ListEntry.h"

template<class S>
class DataList;

template <class S>
class Iterator
{
	DataList<S> *data;
	UINT entry;
public:
	Iterator(DataList<S> *data, UINT entry);
	~Iterator(){}

	S Get();
	void Put(S what);

	bool Prev();
	bool Next();

	bool HasPrev();
	bool HasNext();
};

template <class S>
Iterator<S>::Iterator(DataList<S> *data, UINT entry)
{
	this->data = data;
	this->entry = entry;
}

template <class S>
S Iterator<S>::Get()
{
	return data->Read(entry).data;
}

template <class S>
void Iterator<S>::Put(S what)
{
	ListEntry<S> e = data->Read(pos);
	e.data = what;
	data->Write(e, pos);
}

template <class S>
bool Iterator<S>::Prev()
{
	ListEntry<S> e = data->Read(entry);
	if(e.prev != 0)
	{
		entry = e.prev;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::Next()
{
	ListEntry<S> e = data->Read(entry);
	if(e.next != 0)
	{
		entry = e.next;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::HasPrev()
{
	return data->Read(entry).prev != 0;
}

template <class S>
bool Iterator<S>::HasNext()
{
	return data->Read(entry).next != 0;
}