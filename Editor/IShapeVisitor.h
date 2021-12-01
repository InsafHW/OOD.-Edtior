#pragma once
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "OutlineDecorator.h"

class IShapeVisitor
{
public:
	virtual void Visit(Circle const& circle) = 0;
	virtual void Visit(Triangle const& triangle) = 0;
	virtual void Visit(Rectangle const& rectangle) = 0;
	virtual void Visit(OutlineDecorator const& shape) = 0;
	virtual void Visit(CompoundShape const& shape) = 0;
	virtual ~IShapeVisitor() = default;
};

