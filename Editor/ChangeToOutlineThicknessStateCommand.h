#pragma once
#include "ICommand.h"
#include "Canvas.h"

class ChangeToOutlineThicknessStateCommand : public ICommand
{
public:
	ChangeToOutlineThicknessStateCommand(Canvas* canvas, int thickness);
	void Execute() override;
private:
	Canvas* m_canvas;
	int m_thickness;
};

