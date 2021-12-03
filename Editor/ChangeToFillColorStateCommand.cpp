#include "ChangeToFillColorStateCommand.h"

ChangeToFillColorStateCommand::ChangeToFillColorStateCommand(Canvas* canvas, sf::Color color)
	:m_canvas(canvas),
	m_color(color)
{}

void ChangeToFillColorStateCommand::Execute()
{
	m_canvas->SetChangeFillColorState(m_color);
}
