#pragma once
#include "ICommand.h"
#include <iostream>
#include "Canvas.h"

class ReadFromBinCommand : public ICommand
{
public:
	ReadFromBinCommand(Canvas* canvas);
	void Execute() override;
private:
	Canvas* m_canvas;
};