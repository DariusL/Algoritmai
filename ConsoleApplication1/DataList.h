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
	DataList(DataList<S> &&other);
	~DataList(){}

	Iterator<S> Begin();
	Iterator<S> End();
	void Remove(Iterator<S> &it);
	bool Valid(const Iterator<S> &it);
	bool InsertAfter(const Iterator<S> &it, const S &data);
	bool InsertBefore(const Iterator<S> &it, const S &data);
	void PushBack(S &item);
	void Swap(const Iterator<S> &left, const Iterator<S> right);
	void Print();
	bool IsBegin(const Iterator<S> &it);
	bool IsEnd(const Iterator<S> &it);
	bool IsSorted();
	void Clear();
private:
	bool Valid(UINT pos);
	bool Empty(UINT pos);
	UINT New();
	void Create();
};

template <class S>
DataList<S>::DataList(string file) : Data(file)
{
	Create();
	ops += 1;
}

template <class S>
DataList<S>::DataList(DataList<S> &&other) : Data(forward<DataList<S>> (other))
{
	firstMaybeEmpty = other.firstMaybeEmpty;
	ops += 1;
}

template <class S>
Iterator<S> DataList<S>::Begin()
{
	ListHeader header = ReadHeader();
	ops += 2;
	return Iterator<S>(this, header.first);
}

template <class S>
Iterator<S> DataList<S>::End()
{
	ListHeader header = ReadHeader();
	ops += 2;
	return Iterator<S>(this, header.last);
}

template <class S>
void DataList<S>::Remove(Iterator<S> &it)
{
	ops += 1;
	if(Valid(it))
	{
		if(it.entry < firstMaybeEmpty)
			firstMaybeEmpty = it.entry;
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
		ops += 13;
	}
}

template <class S>
bool DataList<S>::Valid(const Iterator<S> &it)
{
	ops += 1;
	return Valid(it.entry);
}

template <class S>
bool DataList<S>::Valid(UINT pos)
{
	ops += 2;
	ListHeader h = ReadHeader();
	return pos != 0;
}

template <class S>
bool DataList<S>::Empty(UINT pos)
{
	ops += 2;
	ListEntry<S> e = Read(pos);
	return e.next == 0 && e.prev == 0;
}

template <class S>
UINT DataList<S>::New()
{
	for(; !Empty(firstMaybeEmpty); firstMaybeEmpty++, ops++);
	ops += 1;
	return firstMaybeEmpty;
}

template <class S>
bool DataList<S>::InsertAfter(const Iterator<S> &it, const S &data)
{
	ops += 1;
	if(IsEnd(it))
	{
		return false;
	}
	else
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
		ops += 20;
		return true;
	}
}

template <class S>
bool DataList<S>::InsertBefore(const Iterator<S> &it, const S &data)
{
	if(IsBegin(it))
	{
		return false;
	}
	else
	{
		ListEntry<S> entry, prev, next;
		UINT entryInd, prevInd, nextInd;

		nextInd = it.entry;
		next = Read(nextInd);
		prevInd = next.prev;
		prev = Read(prevInd);
		entryInd = New();

		entry.data = data;
		entry.prev = prevInd;
		entry.next = nextInd;

		prev.next = entryInd;
		next.prev = entryInd;

		Write(entry, entryInd);
		Write(prev, prevInd);
		Write(next, nextInd);
		ops += 20;
		return true;
	}
}

template <class S>
void DataList<S>::PushBack(S &item)
{
	ListEntry<S> entry, prev, next;
	UINT entryInd, prevInd, nextInd;

	nextInd = ReadHeader().last;
	next = Read(nextInd);
	prevInd = next.prev;
	prev = Read(prevInd);
	entryInd = New();

	entry.data = item;
	entry.prev = prevInd;
	entry.next = nextInd;

	prev.next = entryInd;
	next.prev = entryInd;

	Write(entry, entryInd);
	Write(prev, prevInd);
	Write(next, nextInd);
	ops += 20;
}

template <class S>
void DataList<S>::Swap(const Iterator<S> &left, const Iterator<S> right)
{
	ops += 2;
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
		ops += 10;
	}
}

template <class S>
void DataList<S>::Print()
{
	Iterator<S> b = Begin();
	b.Next();
	ops += 2;
	while(!IsEnd(b))
	{
		cout << b.Get() << endl;
		b.Next();
		ops += 3;
	}
	ops += 2;
	cout << endl;
}

template <class S>
bool DataList<S>::IsBegin(const Iterator<S> &it)
{
	ops += 2;
	ListHeader h = ReadHeader();
	return it.entry == h.first && it.data == this;
}

template <class S>
bool DataList<S>::IsEnd(const Iterator<S> &it)
{
	ops += 2;
	ListHeader h = ReadHeader();
	return it.entry == h.last && it.data == this;
}

template <class S>
bool DataList<S>::IsSorted()
{

	Iterator<S> begin = Begin().GetNext();
	Iterator<S> end = End();
	ops += 5;
	while(!begin.IsNext(end))
	{
		ops += 4;
		if(begin.Get() > begin.GetNext().Get())
			return false;
		ops += 1;
		begin.Next();
	}
	return true;
}

template <class S>
void DataList<S>::Clear()
{
	ops += 2;
	BaseClear();
	Create();
}

template <class S>
void DataList<S>::Create()
{
	ops += 12;
	ListHeader header;
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
	firstMaybeEmpty = SegmentCount();
}