#pragma once
#include "IState.h"
#include "Rectangle.h"

class AddRectangleState : public IState
{
public:
	AddRectangleState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

