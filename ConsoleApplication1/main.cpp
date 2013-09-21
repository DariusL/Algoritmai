#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>

template <class S>
DataList<S> Merge(DataList<S> &data);

template <class S>
DataList<S> Merge(DataList<S> &data, Iterator<S> left, Iterator<S> right);

int main()
{
	default_random_engine gen;
	//uniform_int_distribution<UINT> dist(1, numeric_limits<UINT>::max() - 1);
	uniform_int_distribution<UINT> dist(1, 30);
	auto num = bind(dist, gen);
	DataList<UINT> data("input");
	auto it = data.Begin();
	for(UINT i = 0; i < 100; i++)
		data.InsertAfter(it, num());
	data.Print();
	DataList<UINT> sorted = Merge<UINT>(data);
	sorted.Print();
	system("pause");
	return 0;
}

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
	else if(left.IsNext(right))
	{
		S one = left.Get();
		S two = right.Get();
		if(one < two)
		{
			ret.InsertAfter(begin, one);
			begin.Next();
			ret.InsertAfter(begin, two);
		}
		else
		{
			ret.InsertAfter(begin, two);
			begin.Next();
			ret.InsertAfter(begin, one);
		}
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