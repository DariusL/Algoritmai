#pragma once
#include "DataList.h"
#include "DataHeap.h"

template <class S>
void HeapSort(DataArray<S> &data);

template <class S>
void Heapify(DataArray<S> &data);

template <class S>
void SiftDown(DataArray<S> &data, Iterator<S> start, Iterator<S> end);

template <class S>
void HeapSort(DataList<S> &data);

template <class S>
void HeapSort(DataArray<S> &data)
{
	ops += 3;
	Heapify(data);
	UINT end = data.GetCount() - 1;
	while(end > 0)
	{
		ops += 4;
		data.Swap(0, end);
		end--;
		SiftDown(data, 0, end);
	}
}

template <class S>
void Heapify(DataArray<S> &data)
{
	ops += 4;
	UINT count = data.GetCount();
	UINT start = (count - 2) / 2 + 1;
	do
	{
		ops += 4;
		start--;
		SiftDown(data, start, count - 1);
		
	}while(start != 0);
}

template <class S>
void SiftDown(DataArray<S> &data, UINT start, UINT end)
{
	UINT root = start;
	UINT child = root * 2 + 1;
	UINT swap = root;

	ops += 12;
	if(child <= end)
		if(data[swap] < data[child])
			swap = child;
	child++;
	if(child <= end)
		if(data[swap] < data[child])
			swap = child;
	if(swap != root)
	{
		ops += 2;
		data.Swap(swap, root);
		SiftDown(data, swap, end);
	}
}

template <class S>
void HeapSort(DataList<S> &data)
{
	DataHeap<S> heap("temp heap");
	Iterator<S> it = data.Begin();
	it.Next();
	ops += 9;
	while(!data.IsEnd(it))
	{
		ops += 4;
		heap.Add(it.Get());
		it.Next();
	}
	data.Clear();
	it = data.Begin();
	UINT count = heap.GetCount();
	for(UINT i = 0; i < count; i++)
	{
		ops += 3;
		data.InsertAfter(it, heap.Pop());
	}
}