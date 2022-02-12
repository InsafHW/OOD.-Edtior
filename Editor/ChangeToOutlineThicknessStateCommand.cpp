#include "ChangeToOutlineThicknessStateCommand.h"

ChangeToOutlineThicknessStateCommand::ChangeToOutlineThicknessStateCommand(Canvas* canvas, int thickness)
	:m_canvas(canvas),
	m_thickness(thickness)
{}

void ChangeToOutlineThicknessStateCommand::Execute()
{
	m_canvas->SetChangeOutlineThicknessState(m_thickness);
}
