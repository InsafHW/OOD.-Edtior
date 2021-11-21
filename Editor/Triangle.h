#pragma once
#include "IShape.h"

class Triangle : public IShape
{
public:
	float GetPerimeter() override;
	float GetSquare() override;
	sf::Color GetFillColor() override;
	void Draw(sf::RenderWindow* window) override;
	Triangle(double aX, double aY, double bX, double bY, double cX, double cY);
	sf::FloatRect GetGlobalBounds() override;
	sf::Vector2f GetOrigin() override;
	bool IsSelected() override;
	void Select() override;
	void UnSelect() override;
	void Move(float x, float y) override;
	void ChangeFillColor(sf::Color color) override;
	void ChangeOutlineColor(sf::Color color) override;
	void ChangeOutlineThickness(int size) override;
private:
	sf::ConvexShape m_triangle;
	bool m_isSelected = false;
	float m_AB;
	float m_BC;
	float m_AC;
};

