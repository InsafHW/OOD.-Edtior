#include "ChangeToOutlineColorStateCommand.h"

ChangeToOutlineColorStateCommand::ChangeToOutlineColorStateCommand(Canvas* canvas, sf::Color color)
	:m_canvas(canvas),
	m_color(color)
{}

void ChangeToOutlineColorStateCommand::Execute()
{
	m_canvas->SetChangeOutlineColorState(m_color);
}
