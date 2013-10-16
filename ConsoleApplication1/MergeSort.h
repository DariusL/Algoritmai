#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
void MergeSort(DataList<S> &data);

template <class S>
DataList<S> MergeSort(DataList<S> &data, Iterator<S> left, Iterator<S> right);

template <class S>
void MergeSort(DataArray<S> &data);

template <class S>
DataArray<S> MergeSort(DataArray<S> &data, UINT left, UINT right);


template <class S>
void MergeSort(DataList<S> &data)
{
	data = MergeSort(data, data.Begin().GetNext(), data.End().GetPrev());
	ops += 2;
}

template <class S>
DataList<S> MergeSort(DataList<S> &data, Iterator<S> left, Iterator<S> right)
{
	DataList<S> ret(left.GetSomeString() + " " + right.GetSomeString());
	Iterator<S> end = ret.End();
	S one;
	S two;
	ops += 10;
	if(left == right)
	{
		ops += 2;
		ret.InsertBefore(end, left.Get());
	}
	else
	{
		ops += 15;
		Iterator<S> middle = Iterator<S>::GetMiddleIterator(left, right);
		DataList<S> oneList = MergeSort(data, left, middle.GetPrev());
		DataList<S> twoList = MergeSort(data, middle, right);
		Iterator<S> oneIt = oneList.Begin().GetNext();
		Iterator<S> twoIt = twoList.Begin().GetNext();
		while(!oneList.IsEnd(oneIt) || !twoList.IsEnd(twoIt))
		{
			one = oneIt.Get();
			two = twoIt.Get();
			if(oneList.IsEnd(oneIt) || (!twoList.IsEnd(twoIt) && one > two))
			{
				ret.InsertBefore(end, twoIt.Get());
				twoIt.Next();
			}
			else
			{
				ret.InsertBefore(end, oneIt.Get());
				oneIt.Next();
			}
			ops += 8;
		}
	}
	return ret;
}

template <class S>
void MergeSort(DataArray<S> &data)
{
	data = MergeSort<S>(data, 0, data.GetCount() - 1);
	ops += 2;
}

template <class S>
DataArray<S> MergeSort(DataArray<S> &data, UINT left, UINT right)
{
	ops += 2;
	DataArray<S> ret(to_string(left) + " " + to_string(right), right - left + 1);
	if(left == right)
	{
		ops += 2;
		ret[0] = data[left];
	}
	else
	{
		ops += 14;
		UINT middle1 = (left + right) / 2;
		UINT middle2 = middle1 + 1;
		DataArray<S> oneArr = MergeSort(data, left, middle1);
		DataArray<S> twoArr = MergeSort(data, middle2, right);
		UINT oneIt = 0;
		UINT twoIt = 0;
		UINT oneCount = middle1 - left + 1;
		UINT twoCount = right - middle2 + 1;
		UINT count = right - left + 1;
		S one;
		S two;
		for(UINT i = 0; i < count; i++)
		{
			one = oneIt >= oneCount ? one : oneArr[oneIt];
			two = twoIt >= twoCount ? two : twoArr[twoIt];
			if(oneIt == oneCount || (twoIt != twoCount && one > two))
			{
				ret[i] = two;
				twoIt++;
			}
			else
			{
				ret[i] = one;
				oneIt++;
			}
			ops += 11;
		}
	}
	return ret;
}