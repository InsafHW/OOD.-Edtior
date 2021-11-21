//#pragma once
#include <iostream>
#include "CanvasState.h"
#include "Canvas.h"

class DragAndDropState : public CanvasState
{
public:
	DragAndDropState(Canvas& canvas)
		:m_canvas(canvas)
	{
	}

	void PollEvent(sf::Event event, sf::RenderWindow* window) override
	{
		std::cout << "DragAndDropState";
	};
private:
	Canvas& m_canvas;
};