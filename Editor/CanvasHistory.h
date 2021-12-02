#pragma once
#include "CanvasMemento.h"

class CanvasHistory
{
public:
	void Push(CanvasMemento memento);
	CanvasMemento Pop();
private:
	std::vector<CanvasMemento> m_history;
};
