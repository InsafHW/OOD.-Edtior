#pragma once
#include "Decorator.h"

const auto OUTLINE_COLOR = sf::Color::Green;
const int OUTLINE_THICKNESS = 2;

class OutlineDecorator : public Decorator
{
public:
	OutlineDecorator(IShape* shape);
	void Draw(sf::RenderWindow* window) override;
};

