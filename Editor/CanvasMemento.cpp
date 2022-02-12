#include "CanvasMemento.h"

CanvasMemento::CanvasMemento(std::list<CompoundShape*> shapes, std::list<CompoundShape*> selectedShapes)
	:m_selectedShapes(selectedShapes)
{
	for (auto it = shapes.begin(); it != shapes.end(); it++)
	{
		m_shapes.push_back({ *it, (*it)->GetFillColor() });
	}
};
