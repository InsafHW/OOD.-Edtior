#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "CompoundShape.h"
#include "Builder.h"

class FilesShapeReader
{
public:
	std::list<CompoundShape*> GetShapes() const;
protected:
	void StartReading() const;
	virtual std::list<CompoundShape*> ReadShapes() const = 0;
	virtual void PrintReadingFileTypeHook() const {}
	virtual void EndlineHook() const;
private:
	std::unique_ptr<Builder> m_builder;
};

