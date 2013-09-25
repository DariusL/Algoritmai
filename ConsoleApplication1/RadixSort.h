#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
void RadixSort(DataArray<S> &data);

template <class S>
void RadixSort(DataList<S> &data);

template <class S>
void RadixSort(DataArray<S> &data)
{
	UINT count = data.GetCount();
	DataArray<S> one("one", 0);
	DataArray<S> zero("zero", 0);
	UINT byteCount = sizeof(S);
	UINT bitMask, masked = 0, ind, oneCount, zeroCount;
	S item;
	for(UINT i = 0; i < byteCount; i++)
	{
		for(UINT j = 0; j < 8; j++)
		{
			bitMask = 1 << j;
			for(UINT k = 0; k < count; k++)
			{
				item = data[k];
				memcpy(&masked, ((char*)&item) + i, 1);
				if(masked & bitMask)
					one.PushBack(item);
				else
					zero.PushBack(item);
			}
			ind = 0;
			oneCount = one.GetCount();
			zeroCount = zero.GetCount();
			for(UINT l = 0; l < zeroCount; l++, ind++)
				data[ind] = zero[l];
			for(UINT l = 0; l < oneCount; l++, ind++)
				data[ind] = one[l];
			one.Clear();
			zero.Clear();
		}
	}
}

template <class S>
void RadixSort(DataList<S> &data)
{
	DataList<S> one("one");
	DataList<S> zero("zero");
	UINT byteCount = sizeof(S);
	UINT bitMask, masked = 0;
	S item;
	Iterator<S> mit, oit, zit;
	oit = one.End();
	zit = zero.End();
	for(UINT i = 0; i < byteCount; i++)
	{
		for(UINT j = 0; j < 8; j++)
		{
			bitMask = 1 << j;
			mit = data.Begin();
			for(mit.Next(); !data.IsEnd(mit); mit.Next())
			{
				item = mit.Get();
				memcpy(&masked, ((char*)&item) + i, 1);
				if(masked & bitMask)
					one.InsertBefore(oit, item);
				else
					zero.InsertBefore(zit, item);
			}
			data.Clear();
			mit = data.End();
			zit = zero.Begin();
			oit = one.Begin();
			for(zit.Next(); !zero.IsEnd(zit); zit.Next())
				data.InsertBefore(mit, zit.Get());
			for(oit.Next(); !one.IsEnd(oit); oit.Next())
				data.InsertBefore(mit, oit.Get());
			one.Clear();
			zero.Clear();
		}
	}
}