#pragma once
#include "ListEntry.h"

template<class S>
class DataList;

template <class S>
class Iterator
{
	friend class DataList<S>;
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

	void Remove();
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
	if(!data->Valid(entry))
		return;
	ListEntry<S> e = data->Read(pos);
	e.data = what;
	data->Write(e, pos);
}

template <class S>
bool Iterator<S>::Prev()
{
	ListEntry<S> e = data->Read(entry);
	if(data->Valid(e.prev))
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
	if(data->Valid(e.next))
	{
		entry = e.next;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::HasPrev()
{
	UINT prev = data->Read(entry).prev;
	return data->Valid(prev);
}

template <class S>
bool Iterator<S>::HasNext()
{
	UINT next = data->Read(entry).next;
	return data->Valid(next);
}

template <class S>
void Iterator<S>::Remove()
{
	
}