#pragma once
#include "ICommand.h"
#include <iostream>
#include "Canvas.h"

class ReadFromTxtCommand : public ICommand
{
public:
	ReadFromTxtCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};