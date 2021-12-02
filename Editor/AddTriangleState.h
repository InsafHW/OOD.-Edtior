#pragma once
#include "IState.h"
#include "Triangle.h"

class AddTriangleState : public IState
{
public:
	AddTriangleState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

