#include "ChangeToAddCircleStateCommand.h"

ChangeToAddCircleStateCommand::ChangeToAddCircleStateCommand(Canvas* canvas)
	:m_canvas(canvas)
{}

void ChangeToAddCircleStateCommand::Execute()
{
	m_canvas->SetAddCircleState();
}
