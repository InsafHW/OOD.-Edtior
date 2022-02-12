#include "BinaryReader.h"

std::list<CompoundShape*> BinaryReader::ReadShapes() const
{
	CircleBuilder circleBuilder;
	RectangleBuilder rectangleBuilder;
	TriangleBuilder triangleBuilder;

	std::ifstream input;
	std::list<CompoundShape*> shapes;
	SavedShapeData data;
	int size = 0;

	input.open("data.bin", std::ios::binary);
	input.seekg(0, std::ios::end);
	size = input.tellg();
	input.close();

	input.open("data.bin", std::ios::binary);

	for (int i = 0; i < size; i += sizeof(data))
	{
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

void BinaryReader::PrintReadingFileTypeHook() const
{
	std::cout << "Binary Type";
}