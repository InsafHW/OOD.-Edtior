#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "CompoundShape.h"

class FilesShapeReader
{
public:
	std::list<CompoundShape*> GetShapes() const
	{
		std::ifstream& input = this->GetInputFile();
		return ReadShapes();
	};

protected:
	std::ifstream& GetInputFile() const {
		std::ifstream input;
		return input;
	}

	virtual std::list<CompoundShape*> ReadShapes() const = 0;

	virtual void Hook1() const {}
	virtual void Hook2() const {}
};

