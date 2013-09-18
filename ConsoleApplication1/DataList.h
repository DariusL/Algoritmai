#pragma once

#include "Data.h"
#include "Iterator.h"
template <class T>
class DataList : public Data<T>
{
	friend class Iterator;
	DataList(string file) : Data(file){}
	~DataList(){}

	Iterator<T> Begin();
};

template <class T>
Iterator<T> DataList<T>::Begin()
{
	return Iterator<T>(this);
}