#include "Singleton.h"

Singleton& Singleton::GetInstance(std::list<CompoundShape*> shapes)
{
	static Singleton instance(shapes);
	return instance;
}

void Singleton::AddShape(CompoundShape* shape)
{
	m_shapes.push_back(shape);
}

void Singleton::PollEvents()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::KeyPressed:
			if (m_event.key.code == sf::Keyboard::LShift)
			{
				m_lShiftPressed = true;
			}
			if (m_event.key.code == sf::Keyboard::LControl)
			{
				m_ctrlPressed = true;
			};
			if (m_ctrlPressed && m_event.key.code == sf::Keyboard::G && m_selectedShapes.size() > 1)
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
			if (m_ctrlPressed && m_event.key.code == sf::Keyboard::U)
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
			if (m_event.key.code == sf::Keyboard::LShift)
			{
				m_lShiftPressed = false;
			};
			if (m_event.key.code == sf::Keyboard::LControl)
			{
				m_ctrlPressed = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = true;
				int id = 0;
				for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
				{
					if ((*it)->GetGlobalBounds().contains(m_event.mouseButton.x, m_event.mouseButton.y))
					{
						if (m_selectedShapes.size() == 0 && !(*it)->IsSelected())
						{
							(*it)->Select();
							m_selectedShapes.push_back(*it);
						}
						else if (m_lShiftPressed)
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
						};
						m_draggingShapeIdx = id;
						m_draggingShape = true;
						m_mouseShapeOffset.x = m_event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
						m_mouseShapeOffset.y = m_event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
						break;
					}
					id++;
				}
			};
			break;
		case sf::Event::MouseButtonReleased:
			if (m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = false;
				m_draggingShape = false;
			};
			break;
		case sf::Event::MouseMoved:
			m_mouseX = m_event.mouseMove.x;
			m_mouseY = m_event.mouseMove.y;
			break;
		case sf::Event::Closed:
			m_window->close();
			break;
		default:
			break;
		}
	};
}

void Singleton::Update()
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

void Singleton::Render()
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(m_window);
	}
}

void Singleton::Start()
{
	m_window->setKeyRepeatEnabled(false);

	while (m_window->isOpen())
	{
		PollEvents();
		Update();
		m_window->clear();
		Render();
		m_window->display();
	}
}
