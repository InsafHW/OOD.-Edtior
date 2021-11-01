#include "ShapeReader.h"

std::list<IShape*> ShapeReader::ReadShapes(ifstream& input)
{
	std::string line;
	std::string type;
	std::list<IShape*> shapes;
	ofstream output("output.txt");

	while (getline(input, line))
	{
		int typeSeparatorIdx = line.find(":");
		type = line.substr(0, typeSeparatorIdx);
		line = line.substr(typeSeparatorIdx + 1);

		if (type == "RECTANGLE")
		{
			const auto shape = ShapeReader::ParseRectangle(line);
			output << "RECTANGLE: P=" << shape->GetPerimeter() << "; S=" << shape->GetSquare() << std::endl;
			shapes.push_back(shape);
		}
		else if (type == "CIRCLE")
		{
			const auto shape = ShapeReader::ParseCircle(line);
			output << "CIRCLE: P=" << shape->GetPerimeter() << "; S=" << shape->GetSquare() << std::endl;
			shapes.push_back(shape);
		}
		else if (type == "TRIANGLE")
		{
			const auto shape = ShapeReader::ParseTriangle(line);
			output << "TRIANGLE: P=" << shape->GetPerimeter() << "; S=" << shape->GetSquare() << std::endl;
			shapes.push_back(shape);
		}
	}

	return shapes;
}

Circle* ShapeReader::ParseCircle(string str)
{
	int x, y, r;
	int equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	int commaIdx = str.find(",");
	int semicolonIdx = str.find(";");
	x = stoi(str.substr(0, commaIdx));
	y = stoi(str.substr(commaIdx + 1, semicolonIdx));

	str = str.substr(semicolonIdx + 1);
	equalIdx = str.find("=");
	r = stoi(str.substr(equalIdx + 1));

	return new Circle(x, y, r);
}

Rectangle* ShapeReader::ParseRectangle(string str)
{
	int x1, x2, y1, y2;
	int equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	int commaIdx = str.find(",");
	int semicolonIdx = str.find(";");
	x1 = stoi(str.substr(0, commaIdx));
	y1 = stoi(str.substr(commaIdx + 1, semicolonIdx));

	equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	commaIdx = str.find(",");
	semicolonIdx = str.find(";");
	x2 = stoi(str.substr(0, commaIdx));
	y2 = stoi(str.substr(commaIdx + 1, semicolonIdx));

	return new Rectangle(x1, y1, x2, y2);
}

Triangle* ShapeReader::ParseTriangle(string str)
{
	int x1, x2, x3, y1, y2, y3;
	int equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	int commaIdx = str.find(",");
	int semicolonIdx = str.find(";");
	x1 = stoi(str.substr(0, commaIdx));
	y1 = stoi(str.substr(commaIdx + 1, semicolonIdx));

	str = str.substr(semicolonIdx + 1);
	equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	commaIdx = str.find(",");
	semicolonIdx = str.find(";");
	x2 = stoi(str.substr(0, commaIdx));
	y2 = stoi(str.substr(commaIdx + 1, semicolonIdx));

	str = str.substr(semicolonIdx + 1);
	equalIdx = str.find("=");
	str = str.substr(equalIdx + 1);
	commaIdx = str.find(",");
	semicolonIdx = str.find(";");
	x3 = stoi(str.substr(0, commaIdx));
	y3 = stoi(str.substr(commaIdx + 1, semicolonIdx));

	return new Triangle(x1, y1, x2, y2, x3, y3);
}
