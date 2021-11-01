#pragma once
#include <fstream>
#include <string>
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "OutlineDecorator.h"
#include <list>

using namespace std;
class ShapeReader
{
public:
	static std::list<IShape*> ReadShapes(ifstream& input);
private:
	static Circle* ParseCircle(string str);
	static Rectangle* ParseRectangle(string str);
	static Triangle* ParseTriangle(string str);
};