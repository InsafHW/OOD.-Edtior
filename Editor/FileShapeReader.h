#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "CompoundShape.h"
#include "Builder.h"

class FilesShapeReader
{
public:
	std::list<CompoundShape*> GetShapes() const
	{
		this->StartReading();
		PrintReadingFileTypeHook();
		EndlineHook();
		return ReadShapes();
	};

protected:
	void StartReading() const
	{
		std::cout << "Reading... ";
	}

	virtual std::list<CompoundShape*> ReadShapes() const = 0;
	virtual void PrintReadingFileTypeHook() const {}
	virtual void EndlineHook() const
	{
		std::cout << std::endl;
	};

private:
	std::unique_ptr<Builder> m_builder;
};

