#include "OutlineDecorator.h"
#include "CompoundShape.h"
#include "ShapeReader.h"
#include "Application.h"

int main()
{
	ifstream input("input.txt");
	auto input_shapes = ShapeReader::ReadShapes(input);

	std::list<CompoundShape*> shapes;

	//for (auto it = input_shapes.begin(); it != input_shapes.end(); it++)
	//{
	//	CompoundShape* shape = new CompoundShape();
	//	shape->Add(new OutlineDecorator(*it));
	//	shapes.push_back(shape);
	//}

	auto& instance = Application::GetInstance(shapes);
	instance.Start();

	return 0;
};