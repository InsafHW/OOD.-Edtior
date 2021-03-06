#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Rectangle.h"
#include "Button.h"
#include "Canvas.h"
#include "ButtonType.h"
#include "ReadFromBinCommand.h"
#include "ReadFromTxtCommand.h"
#include "ChangeToAddRectangleStateCommand.h"
#include "ChangeToAddCircleStateCommand.h"
#include "ChangeToAddTriangleStateCommand.h"
#include "ChangeToDragAndDropStateCommand.h"
#include "ChangeToFillColorStateCommand.h"
#include "ChangeToOutlineColorStateCommand.h"
#include "ChangeToOutlineThicknessStateCommand.h"

const int BUTTON_SIZE = 24;
const int MARGIN = 20;

class Toolbar
{
public:
	Toolbar(Canvas* canvas);
	void Draw(sf::RenderWindow* window);
	void PollEventAndUpdate(sf::Event event, sf::RenderWindow* window);
	void SetCommand(ICommand* command);
private:
	Canvas* m_canvas;
	std::list<Button> m_buttons;
	std::list<Button> m_thicknesses;
	std::list<Button> m_colors;
	bool m_showColors = false;
	bool m_showThicknesses = false;
	bool m_isFill = false;
	bool m_isOutline = false;
	void ResetExtra();
	ICommand* m_command;
};

