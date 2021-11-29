#include "Canvas.h"

void Canvas::DragAndDropPollEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::LShift)
		{
			m_lShiftPressed = true;
		}
		if (event.key.code == sf::Keyboard::LControl)
		{
			m_ctrlPressed = true;
		};
		if (event.key.code == sf::Keyboard::Delete)
		{
			for (auto it = m_selectedShapes.begin(); it != m_selectedShapes.end(); it++)
			{
				m_shapes.remove(*it);
			}
			m_selectedShapes.clear();
		};
		if (m_ctrlPressed && event.key.code == sf::Keyboard::G && m_selectedShapes.size() > 1)
		{
			CompoundShape* comp = new CompoundShape();
			for (auto it = m_selectedShapes.begin(); it != m_selectedShapes.end(); it++)
			{
				auto shapes = (*it)->GetShapes();
				for (auto innerIt = shapes.begin(); innerIt != shapes.end(); innerIt++)
				{
					comp->Add(*innerIt);
					(*innerIt)->UnSelect();
				}
				m_shapes.remove(*it);
				delete* it;
			}
			m_shapes.push_back(comp);
			m_selectedShapes.clear();
			m_selectedShapes.push_back(comp);
			m_draggingShapeIdx = m_shapes.size() - 1;
		}
		if (m_ctrlPressed && event.key.code == sf::Keyboard::U)
		{
			auto compound = *std::next(m_shapes.begin(), m_draggingShapeIdx);
			auto shapes = compound->GetShapes();
			if (shapes.size() > 1)
			{
				for (auto it = shapes.begin(); it != shapes.end(); it++)
				{
					CompoundShape* soloShape = new CompoundShape();
					soloShape->Add(*it);
					soloShape->Select();
					m_shapes.push_back(soloShape);
					m_selectedShapes.push_back(soloShape);
				}
				m_selectedShapes.remove(compound);
				m_shapes.remove(compound);
				delete compound;
			}
		};
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::LShift)
		{
			m_lShiftPressed = false;
		};
		if (event.key.code == sf::Keyboard::LControl)
		{
			m_ctrlPressed = false;
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_mouseClicked = true;
			int id = 0;
			for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
			{
				if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					if (m_lShiftPressed)
					{
						if ((*it)->IsSelected())
						{
							(*it)->Unselect();
							m_selectedShapes.remove(*it);
						}
						else
						{
							(*it)->Select();
							m_selectedShapes.push_back(*it);
						}
					}
					else
					{
						for (auto it = m_selectedShapes.begin(); it != m_selectedShapes.end(); it++)
						{
							(*it)->Unselect();
						}
						(*it)->Select();
						m_selectedShapes.clear();
						m_selectedShapes.push_back(*it);

					}
					m_draggingShapeIdx = id;
					m_draggingShape = true;
					m_mouseShapeOffset.x = event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
					m_mouseShapeOffset.y = event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
					break;
				}
				id++;
			}
		};
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_mouseClicked = false;
			m_draggingShape = false;
		};
		break;
	case sf::Event::MouseMoved:
		m_mouseX = event.mouseMove.x;
		m_mouseY = event.mouseMove.y;
		break;
	default:
		break;
	}
}

void Canvas::AddRectanglePollEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.y > 30)
		{
			CompoundShape* shape = new CompoundShape();
			shape->Add(new OutlineDecorator(new Rectangle(event.mouseButton.x, event.mouseButton.y, event.mouseButton.x + 100, event.mouseButton.y + 100)));
			m_shapes.push_back(shape);
		};
		break;
	default:
		break;
	}
}

void Canvas::AddTrianglePollEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.y > 30)
		{
			CompoundShape* shape = new CompoundShape();
			shape->Add(new OutlineDecorator(new Triangle(event.mouseButton.x, event.mouseButton.y + 100, event.mouseButton.x + 100, event.mouseButton.y, event.mouseButton.x + 200, event.mouseButton.y + 100)));
			m_shapes.push_back(shape);
		};
		break;
	default:
		break;
	}
}

void Canvas::AddCirclePollEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.y > 30)
		{
			CompoundShape* shape = new CompoundShape();
			shape->Add(new OutlineDecorator(new Circle(event.mouseButton.x, event.mouseButton.y, 100)));
			m_shapes.push_back(shape);
		};
		break;
	default:
		break;
	}
}

void Canvas::ChangeFillColorPollEvent(sf::Event event, sf::RenderWindow* window)
{

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
			{
				if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "ChangeFillColorPollEvent\n";

					(*it)->ChangeFillColor(m_color);
					break;
				}
			}
		};
		break;
	default:
		break;
	}
}

void Canvas::ChangeOutlineColorPollEvent(sf::Event event, sf::RenderWindow* window)
{

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
			{
				if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "ChangeFillColorPollEvent\n";

					(*it)->ChangeOutlineColor(m_color);
					break;
				}
			}
		};
		break;
	default:
		break;
	}
}

void Canvas::ChangeOutlineThicknessPollEvent(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
			{
				if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "ChangeOutlineThicknessPollEvent\n";

					(*it)->ChangeOutlineThickness(m_size);
					break;
				}
			}
		};
		break;
	default:
		break;
	}
}

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
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(window);
	}
}
