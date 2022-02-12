#include "TriangleBuilder.h"

OutlineDecorator* TriangleBuilder::ProduceFigure(SavedShapeData& data)
{
	float aX = data.topLeftX;
	float aY = data.topLeftY + data.height;
	float bX = data.topLeftX + data.width / 2;
	float bY = data.topLeftY;
	float cX = data.topLeftX + data.width;
	float cY = data.topLeftY + data.height;

	auto triangle = new OutlineDecorator(new Triangle(aX, aY, bX, bY, cX, cY));
	triangle->ChangeFillColor(data.fillColor);
	triangle->ChangeOutlineColor(data.outlineColor);

	return triangle;
};