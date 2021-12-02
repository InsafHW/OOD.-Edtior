#pragma once
#include "Builder.h"
#include "Circle.h"

class CircleBuilder : public Builder
{
public:
	OutlineDecorator* ProduceFigure(SavedShapeData& data) override;
};

