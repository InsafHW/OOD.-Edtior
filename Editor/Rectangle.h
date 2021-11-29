#pragma once
#include "IShape.h"

class Rectangle : public IShape
{
public:
	float GetPerimeter() override;
	float GetSquare() override;
	void Draw(sf::RenderWindow* window) override;
	Rectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY);
	sf::FloatRect GetGlobalBounds() override;
	sf::Vector2f GetOrigin() override;
	bool IsSelected() override;
	void Select() override;
	void UnSelect() override;
	void Move(float x, float y) override;
	void ChangeFillColor(sf::Color color) override;
	void ChangeOutlineColor(sf::Color color) override;
	void ChangeOutlineThickness(int size) override;
	IShapeType GetType() override;
private:
	sf::RectangleShape m_rectangle;
	bool m_isSelected = false;
};

