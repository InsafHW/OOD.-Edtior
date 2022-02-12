#pragma once
#include "IState.h"

class ChangeFillColorState : public IState
{
public:
	ChangeFillColorState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

