#pragma once
#include "Builder.h"
#include "Rectangle.h"

class RectangleBuilder : Builder
{
public:
	OutlineDecorator* ProduceFigure(SavedShapeData& data) override;
};

