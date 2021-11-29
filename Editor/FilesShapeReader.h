#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "CompoundShape.h"

class FilesShapeReader
{
public:
	std::list<CompoundShape*> GetShapes(std::string path) const
	{
		std::ifstream& input = this->GetInputFile();
		return ReadShapes(input);
	};

protected:
	std::ifstream& GetInputFile() const {
		std::ifstream input;
		return input;
	}

	virtual std::list<CompoundShape*> ReadShapes(std::ifstream& input) const = 0;

	virtual void Hook1() const {}
	virtual void Hook2() const {}
};

