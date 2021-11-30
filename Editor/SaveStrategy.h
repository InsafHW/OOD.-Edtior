#pragma once
#include <string>
#include "CompoundShape.h"
#include <list>

struct SaveStrategy
{
	virtual ~SaveStrategy() {};
	virtual void SaveFile(std::list<CompoundShape*> shapes) = 0;
};

