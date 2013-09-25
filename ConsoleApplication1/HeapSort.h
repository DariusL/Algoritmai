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
	Heapify(data);
	UINT end = data.GetCount() - 1;
	while(end > 0)
	{
		data.Swap(0, end);
		end--;
		SiftDown(data, 0, end);
	}
}

template <class S>
void Heapify(DataArray<S> &data)
{
	UINT count = data.GetCount();
	UINT start = (count - 2) / 2;
	while(true)
	{
		SiftDown(data, start, count - 1);
		if(start == 0)
			break;
		start--;
	}
}

template <class S>
void SiftDown(DataArray<S> &data, UINT start, UINT end)
{
	UINT root = start;
	UINT child, swap;

	while(root * 2 + 1 <= end)
	{
		child = root * 2 + 1;
		swap = root;
		if(data[swap] < data[child])
			swap = child;
		if(child + 1 <= end)
			if(data[swap] < data[child + 1])
				swap = child + 1;
		if(swap != root)
		{
			data.Swap(swap, root);
			root = swap;
		}
		else
		{
			break;
		}
	}
}

template <class S>
void HeapSort(DataList<S> &data)
{
	DataHeap<S> heap("temp heap");
	Iterator<S> it = data.Begin();
	it.Next();
	while(!data.IsEnd(it))
	{
		heap.Add(it.Get());
		it.Next();
	}
	data.Clear();
	it = data.Begin();
	UINT count = heap.GetCount();
	for(UINT i = 0; i < count; i++)
	{
		data.InsertAfter(it, heap.Pop());
	}
}