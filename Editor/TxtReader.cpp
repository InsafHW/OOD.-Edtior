#include "TxtReader.h"

std::list<CompoundShape*> TxtReader::ReadShapes() const
{
	CircleBuilder circleBuilder;
	RectangleBuilder rectangleBuilder;
	TriangleBuilder triangleBuilder;

	std::ifstream input;
	std::list<CompoundShape*> shapes;
	SavedShapeData data;

	input.open("data.txt");

	while (!input.eof())
	{
		std::cout << 1;
		CompoundShape* shape = new CompoundShape();
		input.read((char*)&data, sizeof(data));

		if (data.type == IShapeType::CIRCLE)
		{
			shape->Add(circleBuilder.ProduceFigure(data));
		}
		else if (data.type == IShapeType::RECTANGLE)
		{
			shape->Add(rectangleBuilder.ProduceFigure(data));
		}
		else
		{
			shape->Add(triangleBuilder.ProduceFigure(data));
		}
		shapes.push_back(shape);
	}
	return shapes;
}

void TxtReader::PrintReadingFileTypeHook() const
{
	std::cout << "Txt Type";
}