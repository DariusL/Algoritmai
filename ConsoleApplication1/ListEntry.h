#pragma once

#include "Globals.h"

template <class S>
struct ListEntry
{
	S data;
	UINT next;
	UINT prev;

	ListEntry():data(), next(0), prev(0){}
};