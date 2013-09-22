#pragma once
#include "DataArray.h"
#include "DataList.h"

template <class S>
DataList<S> Merge(DataList<S> &data);

template <class S>
DataList<S> Merge(DataList<S> &data, Iterator<S> left, Iterator<S> right);

template <class S>
DataArray<S> Merge(DataArray<S> &data);

template <class S>
DataArray<S> Merge(DataArray<S> &data, UINT left, UINT right);


template <class S>
DataList<S> Merge(DataList<S> &data)
{
	return Merge(data, data.Begin().GetNext(), data.End().GetPrev());
}

template <class S>
DataList<S> Merge(DataList<S> &data, Iterator<S> left, Iterator<S> right)
{
	DataList<S> ret(left.GetSomeString() + " " + right.GetSomeString());
	Iterator<S> begin = ret.Begin();
	Iterator<S> end = ret.End();
	if(left == right)
	{
		ret.InsertAfter(begin, left.Get());
	}
	else
	{
		Iterator<S> middle = Iterator<S>::GetMiddleIterator(left, right);
		DataList<S> oneList = Merge(data, left, middle.GetPrev());
		DataList<S> twoList = Merge(data, middle, right);
		Iterator<S> oneIt = oneList.Begin().GetNext();
		Iterator<S> twoIt = twoList.Begin().GetNext();
		S one;
		S two;
		while(!oneList.IsEnd(oneIt) || !twoList.IsEnd(twoIt))
		{
			if(oneList.IsEnd(oneIt))
			{
				ret.InsertBefore(end, twoIt.Get());
				twoIt.Next();
			}
			else if(twoList.IsEnd(twoIt))
			{
				ret.InsertBefore(end, oneIt.Get());
				oneIt.Next();
			}
			else
			{
				one = oneIt.Get();
				two = twoIt.Get();
				if(one < two)
				{
					ret.InsertBefore(end, one);
					oneIt.Next();
				}
				else
				{
					ret.InsertBefore(end, two);
					twoIt.Next();
				}
			}
		}
	}
	return ret;
}

template <class S>
DataArray<S> Merge(DataArray<S> &data)
{
	return Merge<S>(data, 0, data.GetCount() - 1);
}

template <class S>
DataArray<S> Merge(DataArray<S> &data, UINT left, UINT right)
{
	DataArray<S> ret(to_string(left) + " " + to_string(right), right - left + 1);
	if(left == right)
	{
		ret[0] = data[left];
	}
	else
	{
		UINT middle1 = (left + right) / 2;
		UINT middle2 = middle1 + 1;
		DataArray<S> oneArr = Merge(data, left, middle1);
		DataArray<S> twoArr = Merge(data, middle2, right);
		UINT oneIt = 0;
		UINT twoIt = 0;
		UINT oneCount = oneArr.GetCount();
		UINT twoCount = twoArr.GetCount();
		UINT count = ret.GetCount();
		S one;
		S two;
		for(UINT i = 0; i < count; i++)
		{
			if(oneIt == oneCount)
			{
				ret[i] = twoArr[twoIt];
				twoIt++;
			}
			else if(twoIt == twoCount)
			{
				ret[i] = oneArr[oneIt];
				oneIt++;
			}
			else
			{
				one = oneArr[oneIt];
				two = twoArr[twoIt];
				if(one < two)
				{
					ret[i] = one;
					oneIt++;
				}
				else
				{
					ret[i] = two;
					twoIt++;
				}
			}
		}
	}
	return ret;
}