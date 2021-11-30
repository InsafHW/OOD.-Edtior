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
		Button fillColorBtn("./img/fillColor.png", (BUTTON_SIZE + MARGIN) * 4, 0, BUTTON_SIZE, ButtonType::CHAGNE_FILL_COLOR_TYPE);
		Button outlineColorBtn("./img/outlineColor.png", (BUTTON_SIZE + MARGIN) * 5, 0, BUTTON_SIZE, ButtonType::CHANGE_OUTLINE_COLOR_TYPE);
		Button thicknessBtn("./img/thickness.png", (BUTTON_SIZE + MARGIN) * 6, 0, BUTTON_SIZE, ButtonType::CHANGE_OUTLINE_THICKNESS_TYPE);
		Button readTxtFile("./img/txt.png", (BUTTON_SIZE + MARGIN) * 7, 0, BUTTON_SIZE, ButtonType::READ_TXT);
		Button readBinFile("./img/bin.png", (BUTTON_SIZE + MARGIN) * 8, 0, BUTTON_SIZE, ButtonType::READ_BIN);

		Button oneThicknessBtn("./img/one.png", (BUTTON_SIZE + MARGIN) * 9, 0, BUTTON_SIZE, ButtonType::THICKNESS_ONE);
		Button twoThicknessBtn("./img/two.png", (BUTTON_SIZE + MARGIN) * 10, 0, BUTTON_SIZE, ButtonType::THICKNESS_TWO);
		Button threeThicknessBtn("./img/three.png", (BUTTON_SIZE + MARGIN) * 11, 0, BUTTON_SIZE, ButtonType::THICKNESS_THREE);

		Button purpleColorBtn("./img/purple.png", (BUTTON_SIZE + MARGIN) * 9, 0, BUTTON_SIZE, ButtonType::PURPLE_COLOR);
		Button yellowColorBtn("./img/yellow.png", (BUTTON_SIZE + MARGIN) * 10, 0, BUTTON_SIZE, ButtonType::YELLOW_COLOR);
		Button redColorBtn("./img/orange.png", (BUTTON_SIZE + MARGIN) * 11, 0, BUTTON_SIZE, ButtonType::ORANGE_COLOR);

		m_buttons.push_back(createRectangleBtn);
		m_buttons.push_back(createTriangleBtn);
		m_buttons.push_back(createCircleBtn);
		m_buttons.push_back(dragAndDropBtn);
		m_buttons.push_back(fillColorBtn);
		m_buttons.push_back(outlineColorBtn);
		m_buttons.push_back(thicknessBtn);
		m_buttons.push_back(readTxtFile);
		m_buttons.push_back(readBinFile);

		m_thicknesses.push_back(oneThicknessBtn);
		m_thicknesses.push_back(twoThicknessBtn);
		m_thicknesses.push_back(threeThicknessBtn);

		m_colors.push_back(purpleColorBtn);
		m_colors.push_back(yellowColorBtn);
		m_colors.push_back(redColorBtn);
	}

	void Draw(sf::RenderWindow* window)
	{
		sf::RectangleShape toolbarBackground(sf::Vector2f(window->getSize().x, BUTTON_SIZE + 6));
		toolbarBackground.setFillColor(sf::Color::Color(23, 324, 423));
		window->draw(toolbarBackground);

		for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
		{
			(*it).Draw(window);
		}

		if (m_showThicknesses)
		{
			for (auto it = m_thicknesses.begin(); it != m_thicknesses.end(); it++)
			{
				(*it).Draw(window);
			}
		};

		if (m_showColors)
		{
			for (auto it = m_colors.begin(); it != m_colors.end(); it++)
			{
				(*it).Draw(window);
			}
		};
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
					if ((*it).GetButtonType() == ButtonType::READ_BIN)
					{
						m_canvas->ReadFromBin();
						std::cout << "READING BIN..";
					}
					else if ((*it).GetButtonType() == ButtonType::READ_TXT)
					{
						m_canvas->ReadFromTxt();
						std::cout << "READING TXT..";
					}
					else
					{
						(*it).Select();
						for (int i = 0; i < idx; i++)
						{
							(*std::next(m_buttons.begin(), i)).UnSelect();
						}
						for (int i = idx + 1; i < m_buttons.size(); i++)
						{
							(*std::next(m_buttons.begin(), i)).UnSelect();
						}
						ResetExtra();
						switch ((*it).GetButtonType())
						{
						case ButtonType::CREATE_RECTANGLE:
							m_canvas->SetAddRectangleState();
							break;
						case ButtonType::CREATE_TRIANGLE:
							m_canvas->SetAddTriangleState();
							break;
						case ButtonType::CREATE_CIRCLE:
							m_canvas->SetAddCircleState();
							break;
						case ButtonType::DRAG_AND_DROP:
							m_canvas->SetDragAndDropState();
							break;
						case ButtonType::CHAGNE_FILL_COLOR_TYPE:
							m_showColors = true;
							m_isFill = true;
							m_canvas->SetChangeFillColorState(sf::Color::Color(138, 43, 226));
							break;
						case ButtonType::CHANGE_OUTLINE_COLOR_TYPE:
							m_showColors = true;
							m_isOutline = true;
							m_canvas->SetChangeOutlineColorState(sf::Color::Color(138, 43, 226));
							break;
						case ButtonType::CHANGE_OUTLINE_THICKNESS_TYPE:
							m_showThicknesses = true;
							m_canvas->SetChangeOutlineThicknessState(1);
							break;
						}
					}

				}
				idx++;
			}
			if (m_showColors)
			{
				for (auto it = m_colors.begin(); it != m_colors.end(); it++)
				{
					if ((*it).GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						switch ((*it).GetButtonType())
						{
						case ButtonType::PURPLE_COLOR:
							if (m_isFill)
							{
								m_canvas->SetChangeFillColorState(sf::Color::Color(138, 43, 226));
							}
							else if (m_isOutline)
							{
								m_canvas->SetChangeOutlineColorState(sf::Color::Color(138, 43, 226));
							}
							break;
						case ButtonType::ORANGE_COLOR:
							if (m_isFill)
							{
								m_canvas->SetChangeFillColorState(sf::Color::Color(255, 165, 0));
							}
							else if (m_isOutline)
							{
								m_canvas->SetChangeOutlineColorState(sf::Color::Color(255, 165, 0));
							}
							break;
						case ButtonType::YELLOW_COLOR:
							if (m_isFill)
							{
								m_canvas->SetChangeFillColorState(sf::Color::Yellow);
							}
							else if (m_isOutline)
							{
								m_canvas->SetChangeOutlineColorState(sf::Color::Yellow);
							}
							break;
						}
					}
				}
			}
			if (m_showThicknesses)
			{
				for (auto it = m_thicknesses.begin(); it != m_thicknesses.end(); it++)
				{
					if ((*it).GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						switch ((*it).GetButtonType())
						{
						case ButtonType::THICKNESS_ONE:
							m_canvas->SetChangeOutlineThicknessState(1);
							break;
						case ButtonType::THICKNESS_TWO:
							m_canvas->SetChangeOutlineThicknessState(2);
							break;
						case ButtonType::THICKNESS_THREE:
							m_canvas->SetChangeOutlineThicknessState(3);
							break;
						}
					}
				}
			}

			break;
		default:
			break;
		}
	};

private:
	Canvas* m_canvas;
	std::list<Button> m_buttons;
	std::list<Button> m_thicknesses;
	std::list<Button> m_colors;
	bool m_showColors = false;
	bool m_showThicknesses = false;
	bool m_isFill = false;
	bool m_isOutline = false;
	void ResetExtra()
	{
		m_showColors = false;
		m_showThicknesses = false;
		m_isFill = false;
		m_isOutline = false;
	};
};

