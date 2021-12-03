#include "ChangeToAddTriangleStateCommand.h"

ChangeToAddTriangleStateCommand::ChangeToAddTriangleStateCommand(Canvas* canvas)
	:m_canvas(canvas)
{}

void ChangeToAddTriangleStateCommand::Execute()
{
	m_canvas->SetAddTriangleState();
}
