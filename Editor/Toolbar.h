#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Rectangle.h"
#include "Button.h"
#include "Canvas.h"
#include "ButtonType.h"

const int BUTTON_SIZE = 24;
const int MARGIN = 20;

class Toolbar
{
public:
	Toolbar(Canvas* canvas)
		:m_canvas(canvas)
	{
		Button createRectangleBtn("./img/rectangle.png", 0, 0, BUTTON_SIZE, ButtonType::CREATE_RECTANGLE);
		Button createTriangleBtn("./img/triangle.png", BUTTON_SIZE + MARGIN, 0, BUTTON_SIZE, ButtonType::CREATE_TRIANGLE);
		Button createCircleBtn("./img/circle.png", (BUTTON_SIZE + MARGIN) * 2, 0, BUTTON_SIZE, ButtonType::CREATE_CIRCLE);
		Button dragAndDropBtn("./img/dragAndDrop.png", (BUTTON_SIZE + MARGIN) * 3, 0, BUTTON_SIZE, ButtonType::DRAG_AND_DROP);

		m_buttons.push_back(createRectangleBtn);
		m_buttons.push_back(createTriangleBtn);
		m_buttons.push_back(createCircleBtn);
		m_buttons.push_back(dragAndDropBtn);
	}

	void Draw(sf::RenderWindow* window)
	{
		sf::RectangleShape toolbarBackground(sf::Vector2f(window->getSize().x, BUTTON_SIZE));
		toolbarBackground.setFillColor(sf::Color::White);
		//window->draw(toolbarBackground);

		for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
		{
			(*it).Draw(window);
		}
	};

	void PollEventAndUpdate(sf::Event event, sf::RenderWindow* window)
	{
		int idx = 0;
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
			{
				if ((*it).GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					std::cout << "BUTTON!";
					(*it).Select();
					for (int i = 0; i < idx; i++)
					{
						(*std::next(m_buttons.begin(), i)).UnSelect();
					}
					for (int i = idx + 1; i < m_buttons.size(); i++)
					{
						(*std::next(m_buttons.begin(), i)).UnSelect();
					}
					switch ((*it).GetButtonType())
					{
					case ButtonType::CREATE_RECTANGLE:
						// state create rectangle
						break;
					case ButtonType::CREATE_TRIANGLE:
						// state create rectangle
						break;
					case ButtonType::CREATE_CIRCLE:
						// state create circle
						break;
					case ButtonType::DRAG_AND_DROP:
						// state drag and drop
						break;
					}
				}
				idx++;
			}
			break;
		default:
			break;
		}
	};

private:
	Canvas* m_canvas;
	std::list<Button> m_buttons;
};

