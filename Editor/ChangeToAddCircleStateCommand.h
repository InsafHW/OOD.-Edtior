#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToAddCircleStateCommand : public ICommand
{
public:
	ChangeToAddCircleStateCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};

