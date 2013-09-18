#pragma once

template<class T>
class DataArray;

template <class T>
class ArrayAcessor
{
	DataArray<T> *data;
	long long ind;
public:
	ArrayAcessor(DataArray<T> *data, long long ind);
	~ArrayAcessor(){}

	operator T();
	void operator =(T data);
};

template<class T>
ArrayAcessor<T>::ArrayAcessor(DataArray<T> *data, long long ind)
{
	this->data = data;
	this->ind = ind;
}

template<class T>
ArrayAcessor<T>::operator T()
{
	return data->Read(ind);
}

template <class T>
void ArrayAcessor<T>::operator=(T data)
{
	this->data->Write(data, ind);
}