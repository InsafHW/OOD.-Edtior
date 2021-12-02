#include "CanvasHistory.h"

void CanvasHistory::Push(CanvasMemento memento)
{
	m_history.push_back(memento);
}

CanvasMemento CanvasHistory::Pop()
{
	auto last = m_history[m_history.size() - 1];
	if (m_history.size() > 1)
	{
		m_history.pop_back();
	}
	return last;
};