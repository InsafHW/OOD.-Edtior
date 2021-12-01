#pragma once
#include "Builder.h"
#include "Rectangle.h"

class RectangleBuilder : Builder
{
public:
	OutlineDecorator* ProduceFigure(SavedShapeData& data) override
	{
		float topLeftX = data.topLeftX;
		float topLeftY = data.topLeftY;
		float bottomRightX = data.topLeftX + data.width;
		float bottomRightY = data.topLeftY + data.height;

		auto rectangle = new OutlineDecorator(new Rectangle(topLeftX, topLeftY, bottomRightX, bottomRightY));
		rectangle->ChangeFillColor(data.fillColor);
		rectangle->ChangeOutlineColor(data.outlineColor);

		return rectangle;
	};
};

