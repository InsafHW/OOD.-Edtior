#pragma once
#include "IShape.h"

class Circle : public IShape
{
public:
	double GetPerimeter() override;
	double GetSquare() override;
	void Draw(sf::RenderWindow* window) override;
	Circle(double centerX, double centerY, double radius);
	sf::FloatRect GetGlobalBounds() override;
	void SetPosition(float x, float y) override;
	sf::Vector2f GetOrigin() override;
	bool IsSelected() override;
	void Select() override;
	void UnSelect() override;
	void Move(float x, float y) override;
	bool IsPartOfCompound() override;
	void SetIsPartOfCompound() override;
	void UnsetIsPartOfCompound() override;
private:
	sf::CircleShape m_circle;
	bool m_isSelected = false;
	bool m_isPartOfCompound = false;
};

