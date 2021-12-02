#include "CircleBuilder.h"

OutlineDecorator* CircleBuilder::ProduceFigure(SavedShapeData& data)
{
	float centerX = data.width / 2 + data.topLeftX;
	float centerY = data.height / 2 + data.topLeftY;
	float radius = data.height / 2;

	auto circle = new OutlineDecorator(new Circle(centerX, centerY, radius));
	circle->ChangeFillColor(data.fillColor);
	circle->ChangeOutlineColor(data.outlineColor);

	return circle;
};