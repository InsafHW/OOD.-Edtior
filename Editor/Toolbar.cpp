#include "Toolbar.h"

Toolbar::Toolbar(Canvas* canvas)
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

void Toolbar::Draw(sf::RenderWindow* window)
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
}
void Toolbar::PollEventAndUpdate(sf::Event event, sf::RenderWindow* window)
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
					SetCommand(new ReadFromBinCommand(m_canvas));
					m_command->Execute();
				}
				else if ((*it).GetButtonType() == ButtonType::READ_TXT)
				{
					SetCommand(new ReadFromTxtCommand(m_canvas));
					m_command->Execute();
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
						SetCommand(new ChangeToAddRectangleStateCommand(m_canvas));
						m_command->Execute();
						break;
					case ButtonType::CREATE_TRIANGLE:
						SetCommand(new ChangeToAddTriangleStateCommand(m_canvas));
						m_command->Execute();
						break;
					case ButtonType::CREATE_CIRCLE:
						SetCommand(new ChangeToAddCircleStateCommand(m_canvas));
						m_command->Execute();
						break;
					case ButtonType::DRAG_AND_DROP:
						SetCommand(new ChangeToDragAndDropStateCommand(m_canvas));
						m_canvas->SetDragAndDropState();
						break;
					case ButtonType::CHAGNE_FILL_COLOR_TYPE:
						m_showColors = true;
						m_isFill = true;
						SetCommand(new ChangeToFillColorStateCommand(m_canvas, sf::Color(138, 43, 226)));
						m_command->Execute();
						break;
					case ButtonType::CHANGE_OUTLINE_COLOR_TYPE:
						m_showColors = true;
						m_isOutline = true;
						SetCommand(new ChangeToOutlineColorStateCommand(m_canvas, sf::Color(138, 43, 226)));
						m_command->Execute();
						break;
					case ButtonType::CHANGE_OUTLINE_THICKNESS_TYPE:
						m_showThicknesses = true;
						SetCommand(new ChangeToOutlineThicknessStateCommand(m_canvas, 1));
						m_command->Execute();
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
							SetCommand(new ChangeToFillColorStateCommand(m_canvas, sf::Color(138, 43, 226)));
							m_command->Execute();
						}
						else if (m_isOutline)
						{
							SetCommand(new ChangeToOutlineColorStateCommand(m_canvas, sf::Color(138, 43, 226)));
							m_command->Execute();
						}
						break;
					case ButtonType::ORANGE_COLOR:
						if (m_isFill)
						{
							SetCommand(new ChangeToFillColorStateCommand(m_canvas, sf::Color::Color(255, 165, 0)));
							m_command->Execute();
						}
						else if (m_isOutline)
						{
							SetCommand(new ChangeToOutlineColorStateCommand(m_canvas, sf::Color(255, 165, 0)));
							m_command->Execute();
						}
						break;
					case ButtonType::YELLOW_COLOR:
						if (m_isFill)
						{
							SetCommand(new ChangeToFillColorStateCommand(m_canvas, sf::Color::Yellow));
							m_command->Execute();
						}
						else if (m_isOutline)
						{
							SetCommand(new ChangeToOutlineColorStateCommand(m_canvas, sf::Color::Yellow));
							m_command->Execute();
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
						SetCommand(new ChangeToOutlineThicknessStateCommand(m_canvas, 1));
						m_command->Execute();
						break;
					case ButtonType::THICKNESS_TWO:
						SetCommand(new ChangeToOutlineThicknessStateCommand(m_canvas, 2));
						m_command->Execute();
						break;
					case ButtonType::THICKNESS_THREE:
						SetCommand(new ChangeToOutlineThicknessStateCommand(m_canvas, 3));
						m_command->Execute();
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void Toolbar::SetCommand(ICommand* command)
{
	m_command = command;
}

void Toolbar::ResetExtra()
{
	m_showColors = false;
	m_showThicknesses = false;
	m_isFill = false;
	m_isOutline = false;
};