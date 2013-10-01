#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
void RadixSort(DataArray<S> &data, UINT speed = 2);

template <class S>
void RadixSort(DataList<S> &data, UINT speed = 2);

template <class S>
void RadixSort(DataArray<S> &data, UINT speed)
{
	UINT count = data.GetCount();
	vector<DataArray<S>> buckets;
	UINT bits = pow(2, speed);
	UINT bucketCount = pow(2, bits);

	for(UINT i = 0; i < bucketCount; i++)
		buckets.emplace_back(to_string(i), 0);

	UINT byteCount = sizeof(S);
	UINT bitMask, masked = 0, ind, bCount, bInd;
	S item;

	for(UINT i = 0; i < byteCount; i++)
	{
		for(UINT j = 0; j < 8; j += bits)
		{
			bitMask = (bucketCount - 1) << j;
			for(UINT k = 0; k < count; k++)
			{
				item = data[k];
				memcpy(&masked, ((char*)&item) + i, 1);
				masked = masked & bitMask;
				bInd = masked >> j;
				buckets[bInd].PushBack(item);
			}
			ind = 0;
			for(UINT b = 0; b < bucketCount; b++)
			{
				DataArray<S> &bucket = buckets[b];
				bCount = bucket.GetCount();

				for(UINT l = 0; l < bCount; l++, ind++)
					data[ind] = bucket[l];
			}
			for(UINT b = 0; b < bucketCount; b++)
				buckets[b].Clear();
		}
	}
}

template <class S>
void RadixSort(DataList<S> &data, UINT speed)
{
	vector<DataList<S>> buckets;
	UINT bits = pow(2, speed);
	UINT bucketCount = pow(2, bits);

	for(UINT i = 0; i < bucketCount; i++)
		buckets.emplace_back(to_string(i));

	UINT byteCount = sizeof(S);
	UINT bitMask, masked = 0, ind = 0;
	S item;
	Iterator<S> mit, it;

	for(UINT i = 0; i < byteCount; i++)
	{
		for(UINT j = 0; j < 8; j += bits)
		{
			bitMask = (bucketCount - 1) << j;
			mit = data.Begin();
			for(mit.Next(); !data.IsEnd(mit); mit.Next())
			{
				item = mit.Get();
				memcpy(&masked, ((char*)&item) + i, 1);
				masked = masked & bitMask;
				ind = masked >> j;
				buckets[ind].PushBack(item);
			}
			data.Clear();
			for(UINT k = 0; k < bucketCount; k++)
			{
				DataList<S> &d = buckets[k];
				it = d.Begin();
				for(it.Next(); !d.IsEnd(it); it.Next())
					data.PushBack(item);
			}
			for(DataList<S> &l : buckets)
				l.Clear();
		}
	}
}