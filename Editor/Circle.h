#pragma once
#include "IShape.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public IShape
{
public:
	float GetPerimeter() override;
	float GetSquare() override;
	void Draw(sf::RenderWindow* window) override;
	Circle(double centerX, double centerY, double radius);
	sf::FloatRect GetGlobalBounds() override;
	sf::Vector2f GetOrigin() override;
	bool IsSelected() override;
	void Select() override;
	void UnSelect() override;
	void Move(float x, float y) override;
private:
	sf::CircleShape m_circle;
	bool m_isSelected = false;
};

