#pragma once
#include "OutlineDecorator.h"

class Builder
{
public:
	virtual OutlineDecorator* ProduceFigure(SavedShapeData& data) = 0;
};

