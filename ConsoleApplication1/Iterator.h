#pragma once
#include "Data.h"

template <class T>
class Iterator
{
	Data<T> *data;
	long long pos;
public:
	Iterator(Data<T> data);
	~Iterator();

	T Get();
	void Put(T what);

	bool Previous();
	bool Next();

	bool HasPrevious();
	bool HasNext();
};

template <class T>
Iterator<T>::Iterator(Data<T> data)
{
	this->data = data;
	pos = 0;
}

template <class T>
T Iterator<T>::Get()
{
	return data->Read(pos);
}

template <class T>
void Iterator<T>::Put(T what)
{
	data->Write(what, pos);
}

template <class T>
bool Iterator<T>::HasPrevious()
{

}