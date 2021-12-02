#pragma once
#include "IState.h"
#include "SaveBinaryStrategy.h"
#include "SaveTxtStrategy.h"

class DragAndDropState : public IState
{
public:
	DragAndDropState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};
