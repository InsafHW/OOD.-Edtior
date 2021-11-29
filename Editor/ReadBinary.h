#pragma once
#include "FilesShapeReader.h"
#include "OutlineDecorator.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

struct BinaryData
{
	float topLeftX;
	float topLeftY;
	float width;
	float height;
	IShapeType type;
	sf::Color fillColor;
	sf::Color outlineColor;
};

class ReadBinary : public FilesShapeReader
{
protected:
	virtual std::list<CompoundShape*> ReadShapes(std::ifstream& input) const override
	{
		std::list<CompoundShape*> shapes;

		BinaryData data;
		input.open("data.bin", std::ios::binary);

		input.seekg(0, std::ios::end);
		int size = input.tellg();
		input.close();

		input.open("data.bin", std::ios::binary);

		for (int i = 0; i < size; i += sizeof(data))
		{
			CompoundShape* shape = new CompoundShape();
			input.read((char*)&data, sizeof(data));
			if (data.type == IShapeType::CIRCLE)
			{
				float centerX = data.width / 2 + data.topLeftX;
				float centerY = data.height / 2 + data.topLeftY;
				float radius = data.height / 2;

				auto circle = new OutlineDecorator(new Circle(centerX, centerY, radius));
				circle->ChangeFillColor(data.fillColor);
				circle->ChangeOutlineColor(data.outlineColor);
				shape->Add(circle);
				std::cout << "Circle" << std::endl;
			}
			else if (data.type == IShapeType::RECTANGLE)
			{
				float topLeftX = data.topLeftX;
				float topLeftY = data.topLeftY;
				float bottomRightX = data.topLeftX + data.width;
				float bottomRightY = data.topLeftY + data.height;

				auto rectangle = new OutlineDecorator(new Rectangle(topLeftX, topLeftY, bottomRightX, bottomRightY));
				rectangle->ChangeFillColor(data.fillColor);
				rectangle->ChangeOutlineColor(data.outlineColor);
				shape->Add(rectangle);
				std::cout << "RECTANGLE" << std::endl;
			}
			else
			{
				float aX = data.topLeftX;
				float aY = data.topLeftY + data.height;
				float bX = data.topLeftX + data.height / 2;
				float bY = data.topLeftY;
				float cX = data.topLeftX + data.width;
				float cY = data.topLeftY + data.height;

				auto triangle = new OutlineDecorator(new Triangle(aX, aY, bX, bY, cX, cY));
				triangle->ChangeFillColor(data.fillColor);
				triangle->ChangeOutlineColor(data.outlineColor);
				shape->Add(triangle);
				std::cout << "Triangle" << std::endl;

			}
			shapes.push_back(shape);
		}
		return shapes;
	};
};

