#pragma once
#include "IShape.h"

class Decorator : public IShape
{
public:
	Decorator(IShape* shape);
	void Draw(sf::RenderWindow* window) override;

	float GetPerimeter() override;
	float GetSquare() override;
	sf::Color GetFillColor() override;
	sf::Color GetOutlineColor() override;
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
protected:
	IShape* m_shape;
};

