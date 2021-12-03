#include "ReadFromBinCommand.h"

ReadFromBinCommand::ReadFromBinCommand(Canvas* canvas)
	:m_canvas(canvas)
{};

void ReadFromBinCommand::Execute()
{
	m_canvas->ReadFromBin();
	std::cout << "READING BIN..";
}
