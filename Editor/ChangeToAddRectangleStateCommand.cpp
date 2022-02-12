#include "ChangeToAddRectangleStateCommand.h"

ChangeToAddRectangleStateCommand::ChangeToAddRectangleStateCommand(Canvas* canvas)
	:m_canvas(canvas)
{}

void ChangeToAddRectangleStateCommand::Execute()
{
	m_canvas->SetAddRectangleState();
}
