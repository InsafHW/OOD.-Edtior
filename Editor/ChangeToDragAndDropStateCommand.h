#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToDragAndDropStateCommand : public ICommand
{
public:
	ChangeToDragAndDropStateCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};

