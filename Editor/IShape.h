#pragma once
#include <SFML/Graphics.hpp>

class IShape
{
public:
	virtual double GetPerimeter() = 0;
	virtual double GetSquare() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;
	virtual sf::FloatRect GetGlobalBounds() = 0;
	virtual void SetPosition(float x, float y) = 0;
	virtual sf::Vector2f GetOrigin() = 0;
	virtual bool IsSelected() = 0;
	virtual void Select() = 0;
	virtual void UnSelect() = 0;
};

