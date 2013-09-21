#pragma once

#include "Data.h"
#include "Iterator.h"
#include "ListEntry.h"
#include "ListHeader.h"
template <class S>
class DataList : public Data<ListHeader, ListEntry<S>>
{
	friend class Iterator<S>;
	UINT firstMaybeEmpty;
public:
	DataList(string file);
	~DataList(){}

	Iterator<S> Begin();
	Iterator<S> End();
	void Remove(Iterator<S> &it);
	bool Valid(const Iterator<S> &it);
	void InsertAfter(const Iterator<S> &it, const S &data);
	void Swap(const Iterator<S> &left, const Iterator<S> right);
	void Print();
	bool IsBegin(const Iterator<S> &it);
	bool IsEnd(const Iterator<S> &it);
private:
	bool Valid(UINT pos);
	bool Empty(UINT pos);
	UINT New();
};

template <class S>
DataList<S>::DataList(string file) : Data(file)
{
	if(IsEmpty())
	{
		ListHeader header;
		header.count = 0;
		header.first = 1;
		header.last = 2;
		WriteHeader(header);
		ListEntry<S> entry;
		entry.prev = 0;
		entry.next = 2;
		Write(entry, 1);
		entry.prev = 1;
		entry.next = 0;
		Write(entry, 2);
	}
	firstMaybeEmpty = SegmentCount();
}

template <class S>
Iterator<S> DataList<S>::Begin()
{
	ListHeader header = ReadHeader();
	return Iterator<S>(this, header.first);
}

template <class S>
Iterator<S> DataList<S>::End()
{
	ListHeader header = ReadHeader();
	return Iterator<S>(this, header.last);
}

template <class S>
void DataList<S>::Remove(Iterator<S> &it)
{
	if(Valid(it))
	{
		if(it.entry < firstMaybeEmpty)
			firstMaybeEmpty = it.entry;
		ListHeader h = ReadHeader();
		h.count--;
		WriteHeader(h);
		ListEntry<S> e = Read(it.entry);
		ListEntry<S> p = Read(e.prev);
		ListEntry<S> n = Read(e.next);
		p.next = e.next;
		n.prev = e.prev;
		e.prev = 0;
		e.next = 0;
		Write(e, it.entry);
		Write(p, n.prev);
		Write(n, p.next);
		it.entry = p.next;
	}
}

template <class S>
bool DataList<S>::Valid(const Iterator<S> &it)
{
	return Valid(it.entry);
}

template <class S>
bool DataList<S>::Valid(UINT pos)
{
	ListHeader h = ReadHeader();
	return pos != 0;
}

template <class S>
bool DataList<S>::Empty(UINT pos)
{
	ListEntry<S> e = Read(pos);
	return e.next == 0 && e.prev == 0;
}

template <class S>
UINT DataList<S>::New()
{
	for(; !Empty(firstMaybeEmpty); firstMaybeEmpty++);
	return firstMaybeEmpty;
}

template <class S>
void DataList<S>::InsertAfter(const Iterator<S> &it, const S &data)
{
	ListEntry<S> entry, prev, next;
	UINT entryInd, prevInd, nextInd;

	prevInd = it.entry;
	prev = Read(prevInd);
	nextInd = prev.next;
	next = Read(nextInd);
	entryInd = New();

	entry.data = data;
	entry.prev = prevInd;
	entry.next = nextInd;

	prev.next = entryInd;
	next.prev = entryInd;

	Write(entry, entryInd);
	Write(prev, prevInd);
	Write(next, nextInd);

	ListHeader h = ReadHeader();
	h.count++;
	WriteHeader(h);
}

template <class S>
void DataList<S>::Swap(const Iterator<S> &left, const Iterator<S> right)
{
	if(Valid(left) && Valid(right))
	{
		ListEntry<S> le = Read(left.entry);
		ListEntry<S> re = Read(right.entry);

		S temp;
		temp = le.data;
		le.data = re.data;
		re.data = temp;

		Write(le, left.entry);
		Write(re, right.entry);
	}
}

template <class S>
void DataList<S>::Print()
{
	Iterator<S> b = Begin();
	b.Next();
	while(!IsEnd(b))
	{
		cout << b.Get() << endl;
		b.Next();
	}
	cout << endl;
}

template <class S>
bool DataList<S>::IsBegin(const Iterator<S> &it)
{
	ListHeader h = ReadHeader();
	return it.entry == h.first;
}

template <class S>
bool DataList<S>::IsEnd(const Iterator<S> &it)
{
	ListHeader h = ReadHeader();
	return it.entry == h.last;
}