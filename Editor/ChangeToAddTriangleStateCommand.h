#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToAddTriangleStateCommand :public ICommand
{
public:
	ChangeToAddTriangleStateCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};

