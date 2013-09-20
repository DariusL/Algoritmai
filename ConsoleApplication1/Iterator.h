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
	Iterator(DataList<S> data, UINT entry);
	~Iterator();

	S Get();
	void Put(S what);

	bool Previous();
	bool Next();

	bool HasPrevious();
	bool HasNext();
};

template <class S>
Iterator<S>::Iterator(DataList<S> data, UINT entry)
{
	this->data = data;
	this->entry = entry;
}

template <class S>
S Iterator<S>::Get()
{
	return data->Read(entry);
}

template <class S>
void Iterator<S>::Put(S what)
{
	data->Write(what, pos);
}

template <class S>
bool Iterator<S>::HasPrevious()
{

}