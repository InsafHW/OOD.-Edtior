#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "IShape.h"
#include "CompoundShape.h"
#include "OutlineDecorator.h"
#include "Circle.h"
#include "Rectangle.h"

class Singleton
{
public:
	static Singleton& getInstance()
	{
		static Singleton instance;
		return instance;
	};

	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;

	void PollEvents()
	{
		while (m_window->pollEvent(m_event))
		{
			if (m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::LShift)
			{
				m_lShiftPressed = true;
			}
			if (m_event.type == sf::Event::KeyReleased && m_event.key.code == sf::Keyboard::LShift)
			{
				m_lShiftPressed = false;
			}
			if (m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::LControl)
			{
				m_ctrlPressed = true;
			}
			if (m_event.type == sf::Event::KeyReleased && m_event.key.code == sf::Keyboard::LControl)
			{
				m_ctrlPressed = false;
			}

			//LMB Pressed
			if (m_event.type == sf::Event::MouseButtonPressed && m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = true;

				for (int i = 0; i < m_shapes.size(); i++)
				{
					if (m_shapes[i]->GetGlobalBounds().contains(m_event.mouseButton.x, m_event.mouseButton.y))
					{
						if (m_lShiftPressed)
						{
							if (m_shapes[i]->IsSelected())
							{
								m_shapes[i]->UnSelect();
							}
							else
							{
								m_shapes[i]->Select();
							}
						}
						m_dragging = true;
						m_dragginItemIdx = i;
						m_mouseShapeOffset.x = m_event.mouseButton.x - m_shapes[i]->GetGlobalBounds().left - m_shapes[i]->GetOrigin().x;
						m_mouseShapeOffset.y = m_event.mouseButton.y - m_shapes[i]->GetGlobalBounds().top - m_shapes[i]->GetOrigin().y;
					}

				};
			}

			if (m_ctrlPressed && m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::U)
			{
				for (auto it = m_compoundShapes.begin(); it != m_compoundShapes.end(); it++)
				{
					m_compoundShapes.remove(*it);
				}
			}

			if (m_ctrlPressed && m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::G)
			{
				CompoundShape* shapes = new CompoundShape();
				for (int i = 0; i < m_shapes.size(); i++)
				{
					if (m_shapes[i]->IsSelected())
					{
						shapes->Add(m_shapes[i]);
					}
				}
				m_compoundShapes.push_back(shapes);
			}

			if (m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_mouseClicked = false;
				m_dragging = false;
			}

			//Mouse Moved in window
			if (m_event.type == sf::Event::MouseMoved)
			{
				m_mouseX = m_event.mouseMove.x;
				m_mouseY = m_event.mouseMove.y;
			}

			//Event type is window closed
			if (m_event.type == sf::Event::Closed)
			{
				m_window->close();
			}

		}
	};

	void Update()
	{
		if (m_dragging == true)
		{
			for (auto it = m_compoundShapes.begin(); it != m_compoundShapes.end(); it++)
			{
				if ((*it)->IsMouseInGroup(m_mouseX, m_mouseY))
				{
					(*it)->Move(m_mouseX, m_mouseY);
				}
			}
		}
		if (m_shapes[m_dragginItemIdx]->IsSelected()) {
			m_shapes[m_dragginItemIdx]->SetPosition(m_mouseX - m_mouseShapeOffset.x, m_mouseY - m_mouseShapeOffset.y);
		}
	}

	void Render()
	{
		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_shapes[i]->Draw(m_window);
		}

		/*for (auto it = m_compoundShapes.begin(); it != m_compoundShapes.end(); it++)
		{
			(*it)->Draw(m_window);
		}*/
	};

	void Start()
	{
		std::cout << "start Start" << std::endl;
		while (m_window->isOpen())
		{
			std::cout << "loop";
			/*PollEvents();
			Update();*/
			m_window->clear();
			Render();
		}
	};

	void AddShape(IShape* shape)
	{
		m_shapes.push_back(shape);
	};

private:
	sf::RenderWindow* m_window;
	sf::Vector2f m_mouseShapeOffset;
	sf::Event m_event;

	bool m_mouseClicked = false;
	bool m_dragging = false;
	bool m_lShiftPressed = false;
	bool m_ctrlPressed = false;
	bool m_hasCompound = false;

	int m_mouseX = 0;
	int m_mouseY = 0;

	int m_dragginItemIdx = 0;
	std::vector<IShape*> m_shapes;
	std::list<CompoundShape*> m_compoundShapes;

	Singleton()
	{
		m_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML Game");
	};
};
