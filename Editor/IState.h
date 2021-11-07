#pragma once
#include "SFML/Graphics.hpp"

struct IState
{
	virtual void PollEvent(sf::Event event, sf::RenderWindow* window) = 0;
};

