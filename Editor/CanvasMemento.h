#pragma once
#include <list>
#include "CompoundShape.h"

struct ShapeState
{
	CompoundShape* shape;
	sf::Color fillColor;
};

class CanvasMemento
{
public:
	CanvasMemento(std::list<CompoundShape*> shapes, std::list<CompoundShape*> selectedShapes);
	std::list<ShapeState> m_shapes;
	std::list<CompoundShape*> m_selectedShapes;
};