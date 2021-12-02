#pragma once
#include <string>
#include "FileShapeReader.h"
#include "OutlineDecorator.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "CircleBuilder.h"
#include "TriangleBuilder.h"
#include "RectangleBuilder.h"

class BinaryReader : public FilesShapeReader
{
protected:
	std::list<CompoundShape*> ReadShapes() const override;
	virtual void PrintReadingFileTypeHook() const override;
};

