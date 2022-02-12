#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToFillColorStateCommand : public ICommand
{
public:
	ChangeToFillColorStateCommand(Canvas* canvas, sf::Color color);
	void Execute() override;
private:
	Canvas* m_canvas;
	sf::Color m_color;
};

