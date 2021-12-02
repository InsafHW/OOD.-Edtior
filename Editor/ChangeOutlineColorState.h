#pragma once
#include "IState.h"

class ChangeOutlineColorState : public IState
{
public:
	ChangeOutlineColorState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

