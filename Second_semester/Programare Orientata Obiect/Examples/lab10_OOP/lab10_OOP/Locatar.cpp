#include "Locatar.h"

bool cmpName(const Locatar& l1, const Locatar& l2)
{
	return l1.getName() < l2.getName();
}

bool cmpSurface(const Locatar& l1, const Locatar& l2)
{
	return l1.getSurface() < l2.getSurface();
}