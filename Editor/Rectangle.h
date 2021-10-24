#pragma once
#include "IShape.h"

class Rectangle : public IShape
{
public:
	double GetPerimeter() override;
	double GetSquare() override;
	void Draw(sf::RenderWindow* window) override;
	Rectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY);
	sf::FloatRect GetGlobalBounds() override;
	void SetPosition(float x, float y) override;
	sf::Vector2f GetOrigin() override;
	bool IsSelected() override;
	void Select() override;
	void UnSelect() override;
private:
	sf::RectangleShape m_rectangle;
	bool m_isSelected = false;
};

