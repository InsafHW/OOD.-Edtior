#pragma once
#include "SaveStrategy.h"
#include <fstream>
#include "IShape.h"

class SaveTxtStrategy : public SaveStrategy
{
public:
	void SaveFile(std::list<CompoundShape*> shapes) override;
};

