#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include "OutlineDecorator.h"
#include "CompoundShape.h"
#include <iostream>
#include "Singleton.h"

int main()
{
	OutlineDecorator* my_circle1 = new OutlineDecorator(new Circle(40, 40, 100));
	OutlineDecorator* my_circle2 = new OutlineDecorator(new Circle(80, 110, 100));
	OutlineDecorator* my_rectangle1 = new OutlineDecorator(new Rectangle(10, 34, 190, 344));
	OutlineDecorator* my_rectangle2 = new OutlineDecorator(new Rectangle(90, 43, 132, 844));

	CompoundShape* c1 = new CompoundShape();
	CompoundShape* c2 = new CompoundShape();
	CompoundShape* r1 = new CompoundShape();
	CompoundShape* r2 = new CompoundShape();

	c1->Add(my_circle1);
	c2->Add(my_circle2);
	r1->Add(my_rectangle1);
	r2->Add(my_rectangle2);

	std::list<CompoundShape*> shapes = { c1, c2, r1,r2 };

	auto& instance = Singleton::GetInstance(shapes);
	instance.Start();

	return 0;
};