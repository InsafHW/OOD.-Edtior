#include "ReadFromTxtCommand.h"

ReadFromTxtCommand::ReadFromTxtCommand(Canvas* canvas)
	:m_canvas(canvas)
{}

void ReadFromTxtCommand::Execute()
{
	m_canvas->ReadFromTxt();
	std::cout << "READING TXT..";
}
