#include "Canvas.h"

void Canvas::Update()
{
	if (m_draggingShape)
	{
		auto candidate = (*std::next(m_shapes.begin(), m_draggingShapeIdx));
		if (candidate)
		{
			if (candidate->GetShapes().size() == 1 && candidate->IsSelected() || candidate->GetShapes().size() > 1)
			{
				candidate->Move(m_mouseX - m_mouseShapeOffset.x, m_mouseY - m_mouseShapeOffset.y);
			}
		};
	}
}

void Canvas::Draw(sf::RenderWindow* window)
{
	std::cout << "m_shapes size = " << m_shapes.size() << " ; m_selectedShapes size = " << m_selectedShapes.size() << std::endl;
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(window);
	}
}
