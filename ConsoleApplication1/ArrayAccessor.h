#pragma once

template<class S>
class DataArray;

template <class S>
class ArrayAcessor
{
	DataArray<S> *data;
	UINT ind;
public:
	ArrayAcessor(DataArray<S> *data, UINT ind);
	~ArrayAcessor(){}

	operator S();
	void operator =(S data);
};

template<class S>
ArrayAcessor<S>::ArrayAcessor(DataArray<S> *data, UINT ind)
{
	this->data = data;
	this->ind = ind;
}

template<class S>
ArrayAcessor<S>::operator S()
{
	return data->Read(ind);
}

template <class S>
void ArrayAcessor<S>::operator=(S data)
{
	this->data->Write(data, ind);
}