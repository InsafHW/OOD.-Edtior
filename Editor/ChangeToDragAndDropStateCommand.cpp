#include "ChangeToDragAndDropStateCommand.h"

ChangeToDragAndDropStateCommand::ChangeToDragAndDropStateCommand(Canvas* canvas)
	:m_canvas(canvas)

{}

void ChangeToDragAndDropStateCommand::Execute()
{
	m_canvas->SetDragAndDropState();
}
