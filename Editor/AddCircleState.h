#pragma once
#include "IState.h"
#include "Circle.h"

class AddCircleState : public IState
{
public:
	AddCircleState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

