#pragma once

#include "Globals.h"

template <class S>
struct ListEntry
{
	S data;
	UINT next;
	UINT prev;
};