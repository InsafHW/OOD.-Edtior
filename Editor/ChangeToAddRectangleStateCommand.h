#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToAddRectangleStateCommand : public ICommand
{
public:
	ChangeToAddRectangleStateCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};

