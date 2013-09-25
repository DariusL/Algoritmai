#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
void RadixSort(DataArray<S> &data);

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