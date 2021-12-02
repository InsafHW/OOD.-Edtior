#pragma once
#include "SaveStrategy.h"
#include <fstream>
#include "IShape.h"

class SaveBinaryStrategy : public SaveStrategy
{
public:
	void SaveFile(std::list<CompoundShape*> shapes) override;
};

