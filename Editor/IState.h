#pragma once
#include <iostream>
#include "ICanvas.h"
#include "SFML/Graphics.hpp"
#include "CompoundShape.h"
#include "OutlineDecorator.h"

struct IState
{
	virtual void PollEvents(sf::Event event, sf::RenderWindow* window) = 0;
};

