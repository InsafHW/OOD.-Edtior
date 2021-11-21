#pragma once
#include "SFML/Graphics.hpp"

class CanvasState
{
public:
	virtual void PollEvent(sf::Event event, sf::RenderWindow* window) = 0;
};

