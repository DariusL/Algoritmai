#pragma once
#include "ListEntry.h"

#include <string>

template<class S>
class DataList;

template <class S>
class Iterator
{
	friend class DataList<S>;
	DataList<S> *data;
	UINT entry;
public:
	Iterator() : data(0), entry(0){}
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
	bool operator!=(const Iterator<S> &other) const {return !(*this == other);ops += 2;}

	static Iterator<S> GetMiddleIterator(const Iterator<S> &left, const Iterator<S> &right);
	string GetSomeString() const {return to_string(entry);ops += 1;}
private:
	ListEntry<S> GetEntry() const;
};

template <class S>
Iterator<S>::Iterator(DataList<S> *data, UINT entry)
{
	ops += 2;
	this->data = data;
	this->entry = entry;
}

template <class S>
S Iterator<S>::Get() const
{
	ops += 2;
	return GetEntry().data;
}

template <class S>
void Iterator<S>::Put(S what) const
{
	ops += 1;
	if(!data->Valid(entry))
		return;
	ops += 4;
	ListEntry<S> e = GetEntry();
	e.data = what;
	data->Write(e, pos);
}

template <class S>
bool Iterator<S>::Prev()
{
	ops += 2;
	ListEntry<S> e = GetEntry();
	if(data->Valid(e.prev))
	{
		ops += 1;
		entry = e.prev;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::Next()
{
	ops += 2;
	ListEntry<S> e = GetEntry();
	if(data->Valid(e.next))
	{
		ops += 1;
		entry = e.next;
		return true;
	}
	return false;
}

template <class S>
bool Iterator<S>::HasPrev() const
{
	ops += 4;
	UINT prev = GetEntry().prev;
	return data->Valid(prev);
}

template <class S>
bool Iterator<S>::HasNext() const
{
	ops += 4;
	UINT next = GetEntry().next;
	return data->Valid(next);
}

template <class S>
void Iterator<S>::Remove()
{
	ops += 2;
	if(HasNext())
	{
		ops += 2;
		ListEntry<S> e = GetEntry();
		entry = e.next;
	}
	data->Remove(*this);
}

template <class S>
bool Iterator<S>::operator==(const Iterator<S> &other) const
{
	ops += 3;
	return data == other.data && entry == other.entry;
}

template <class S>
Iterator<S> Iterator<S>::GetMiddleIterator(const Iterator<S> &left, const Iterator<S> &right)
{
	Iterator<S> it1 = left;
	Iterator<S> it2 = left;
	ops += 3;
	while(it2 != right)
	{
		ops += 5;
		it1.Next();
		it2.Next();
		if(it2 == right)
			break;
		it2.Next();
	}
	return it1;
}

template <class S>
Iterator<S> Iterator<S>::GetNext() const
{
	ops += 2;
	ListEntry<S> e = GetEntry();
	return Iterator<S>(data, e.next);
}

template <class S>
Iterator<S> Iterator<S>::GetPrev() const
{
	ops += 2;
	ListEntry<S> e = GetEntry();
	return Iterator<S>(data, e.prev);
}

template <class S>
bool Iterator<S>::IsNext(const Iterator<S> &other) const
{
	ops += 2;
	return GetNext() == other;
}

template <class S>
bool Iterator<S>::IsPrev(const Iterator<S> &other) const
{
	ops += 2;
	return GetPrev() == other;
}

template <class S>
ListEntry<S> Iterator<S>::GetEntry() const
{
	ops += 2;
	return data->Read(entry);
}