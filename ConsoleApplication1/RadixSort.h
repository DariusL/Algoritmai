#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
void RadixSort(DataArray<S> &data, UINT speed = 2);

template <class S>
void RadixSort(DataList<S> &data, UINT speed = 2);

UINT Clamp(UINT min, UINT max, UINT value);

template <class S>
void RadixSort(DataArray<S> &data, UINT speed)
{
	speed = Clamp(0, 3, speed);
	UINT count = data.GetCount();
	vector<DataArray<S>> buckets;
	UINT bits = pow(2, speed);
	UINT bucketCount = pow(2, bits);
	ops += 5 + bucketCount * 2;
	for(UINT i = 0; i < bucketCount; i++)
		buckets.emplace_back(to_string(i), 0);
	UINT keysPerByte = 8 / bits;
	UINT keyCount = keysPerByte * sizeof(S);
	UINT bitMask, masked = 0, ind, bCount, bInd, inByte, inBit;
	S item;
	ops += 7;
	for (UINT i = 0; i < keyCount; i++)
	{
		inByte = i / keysPerByte;
		inBit = (i % keysPerByte) * bits;
		bitMask = (bucketCount - 1) << inBit;

		for (UINT k = 0; k < count; k++)
		{
			ops += 5;
			item = data[k];
			memcpy(&masked, ((char*)&item) + inByte, 1);
			masked &= bitMask;
			bInd = masked >> inBit;
			buckets[bInd].PushBack(item);
		}
		ind = 0;
		for (UINT b = 0; b < bucketCount; b++)
		{

			DataArray<S> &bucket = buckets[b];
			bCount = bucket.GetCount();
			ops += 4 + bCount * 3;
			for (UINT l = 0; l < bCount; l++, ind++)
				data[ind] = bucket[l];
		}
		ops += bucketCount;
		for (UINT b = 0; b < bucketCount; b++)
			buckets[b].Clear();
	}
}

template <class S>
void RadixSort(DataList<S> &data, UINT speed)
{
	speed = Clamp(0, 3, speed);
	vector<DataList<S>> buckets;
	UINT bits = pow(2, speed);
	UINT bucketCount = pow(2, bits);
	ops += 4 + bucketCount * 2;
	for(UINT i = 0; i < bucketCount; i++)
		buckets.emplace_back(to_string(i));
	UINT keysPerByte = 8 / bits;
	UINT keyCount = keysPerByte * sizeof(S);
	UINT bitMask, masked = 0, ind = 0, inBit, inByte;
	S item;
	Iterator<S> mit, it;
	ops += 7;
	for (UINT i = 0; i < keyCount; i++)
	{
		inByte = i / keysPerByte;
		inBit = (i % keysPerByte) * bits;
		bitMask = (bucketCount - 1) << inBit;
		mit = data.Begin();
		for(mit.Next(); !data.IsEnd(mit); mit.Next())
		{
			ops += 7;
			item = mit.Get();
			memcpy(&masked, ((char*)&item) + inByte, 1);
			masked = masked & bitMask;
			ind = masked >> inBit;
			buckets[ind].PushBack(item);
		}
		data.Clear();
		for(UINT k = 0; k < bucketCount; k++)
		{
			ops += 4;
			DataList<S> &d = buckets[k];
			it = d.Begin();
			for(it.Next(); !d.IsEnd(it); it.Next())
			{
				ops += 2;
				data.PushBack(item);
			}
		}
		ops += bucketCount;
		for(DataList<S> &l : buckets)
			l.Clear();
	}
}

UINT Clamp(UINT min, UINT max, UINT value)
{
	ops += 3;
	if(value < min)
		return min;
	else if(value > max)
		return max;
	else
		return value;
}