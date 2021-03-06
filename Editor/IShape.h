#pragma once
#include <SFML/Graphics.hpp>

enum class IShapeType
{
	CIRCLE,
	RECTANGLE,
	TRIANGLE
};


struct SavedShapeData
{
	float topLeftX;
	float topLeftY;
	float width;
	float height;
	IShapeType type;
	sf::Color fillColor;
	sf::Color outlineColor;
};

class IShape
{
public:
	virtual float GetPerimeter() = 0;
	virtual float GetSquare() = 0;
	virtual sf::Color GetFillColor() = 0;
	virtual sf::Color GetOutlineColor() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;
	virtual sf::FloatRect GetGlobalBounds() = 0;
	virtual sf::Vector2f GetOrigin() = 0;
	virtual bool IsSelected() = 0;
	virtual void Select() = 0;
	virtual void UnSelect() = 0;
	virtual void Move(float x, float y) = 0;
	virtual void ChangeFillColor(sf::Color color) = 0;
	virtual void ChangeOutlineColor(sf::Color color) = 0;
	virtual void ChangeOutlineThickness(int size) = 0;
	virtual IShapeType GetType() = 0;
};

