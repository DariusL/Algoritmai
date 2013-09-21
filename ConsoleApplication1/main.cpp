#include "DataArray.h"
#include "DataList.h"
#include <numeric>
#include <iostream>
#include <random>
#include <functional>
#include <ctime>

template <class S>
void Merge(DataList<S> &data);

template <class S>
void Merge(DataList<S> &data, Iterator<S> left, Iterator<S> right);

int main()
{
	default_random_engine gen;
	//uniform_int_distribution<UINT> dist(1, numeric_limits<UINT>::max() - 5);
	uniform_int_distribution<UINT> dist(1, 30);
	auto num = bind(dist, gen);
	DataList<UINT> data("duomenys.bin");
	auto it = data.Begin();
	for(UINT i = 0; i < 8; i++)
		data.InsertAfter(it, num());
	data.Print();
	//Merge<UINT>(data);
	data.Print();
	data.Delete();
	system("pause");
	return 0;
}

template <class S>
void Merge(DataList<S> &data)
{
	Merge(data, data.Begin().GetNext(), data.End().GetPrev());
}

template <class S>
void Merge(DataList<S> &data, Iterator<S> left, Iterator<S> right)
{
	if(left != right)
	{
		if(left.IsNext(right))
		{
			if(left.Get() > right.Get())
			{
				data.Swap(left, right);
			}
		}
		else
		{
			Iterator<S> middle2 = Iterator<S>::GetMiddleIterator(left, right);
			Iterator<S> middle1 = middle2.GetPrev();
			Merge(data, left, middle1);
			Merge(data, middle2, right);
			Iterator<S> leftIt = left;
			Iterator<S> rightIt = middle2;
			Iterator<S> leftEnd = middle1;
			Iterator<S> rightEnd = right;
			while(!leftIt.IsPrev(leftEnd) || !rightIt.IsPrev(rightEnd))
			{
				if(leftIt.Get() > rightIt.Get())
				{
					data.Swap(leftIt, rightIt);
				}
				leftIt.Next();
				rightIt.Next();
			}
		}
	}
}