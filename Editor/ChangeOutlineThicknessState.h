#pragma once
#include "IState.h"

class ChangeOutlineThicknessState : public IState
{
public:
	ChangeOutlineThicknessState(ICanvas& canvas);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
private:
	ICanvas& m_canvas;
};

