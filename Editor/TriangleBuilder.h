#pragma once
#include "Triangle.h"
#include "Builder.h"

class TriangleBuilder : public Builder
{
public:
	OutlineDecorator* ProduceFigure(SavedShapeData& data) override;
};

