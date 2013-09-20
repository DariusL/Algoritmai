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

	S Get() const;
	void Put(S what) const;

	bool Prev();
	bool Next();

	Iterator<S> GetNext() const;
	Iterator<S> GetPrev() const;

	bool HasPrev() const;
	bool HasNext() const;

	void Remove();

	bool IsNext(const Iterator<S> &other) const;
	bool IsPrev(const Iterator<S> &other) const;

	bool operator==(const Iterator<S> &other) const;
	bool operator!=(const Iterator<S> &other) const {return !(*this == other);}

	static Iterator<S> GetMiddleIterator(const Iterator<S> &left, const Iterator<S> &right);
private:
	ListEntry<S> GetEntry() const;
};

template <class S>
Iterator<S>::Iterator(DataList<S> *data, UINT entry)
{
	this->data = data;
	this->entry = entry;
}

template <class S>
S Iterator<S>::Get() const
{
	return GetEntry().data;
}

template <class S>
void Iterator<S>::Put(S what) const
{
	if(!data->Valid(entry))
		return;
	ListEntry<S> e = GetEntry();
	e.data = what;
	data->Write(e, pos);
}

template <class S>
bool Iterator<S>::Prev()
{
	ListEntry<S> e = GetEntry();
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
	ListEntry<S> e = GetEntry();
	if(data->Valid(e.next))
	{
		entry = e.next;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::HasPrev() const
{
	UINT prev = GetEntry().prev;
	return data->Valid(prev);
}

template <class S>
bool Iterator<S>::HasNext() const
{
	UINT next = GetEntry().next;
	return data->Valid(next);
}

template <class S>
void Iterator<S>::Remove()
{
	if(HasNext())
	{
		ListEntry<S> e = GetEntry();
		entry = e.next;
	}
	data->Remove(*this);
}

template <class S>
bool Iterator<S>::operator==(const Iterator<S> &other) const
{
	return data == other.data && entry == other.entry;
}

template <class S>
Iterator<S> Iterator<S>::GetMiddleIterator(const Iterator<S> &left, const Iterator<S> &right)
{
	Iterator<S> it1 = left;
	Iterator<S> it2 = left;
	while(it2 != right)
	{
		it1.Next();
		it2.Next();
		it2.Next();
	}
	return it1;
}

template <class S>
Iterator<S> Iterator<S>::GetNext() const
{
	ListEntry<S> e = GetEntry();
	return Iterator<S>(data, e.next);
}

template <class S>
Iterator<S> Iterator<S>::GetPrev() const
{
	ListEntry<S> e = GetEntry();
	return Iterator<S>(data, e.prev);
}

template <class S>
bool Iterator<S>::IsNext(const Iterator<S> &other) const
{
	return GetNext() == other;
}

template <class S>
bool Iterator<S>::IsPrev(const Iterator<S> &other) const
{
	return GetPrev() == other;
}

template <class S>
ListEntry<S> Iterator<S>::GetEntry() const
{
	return data->Read(entry);
}