#include "Rectangle.h"

double Rectangle::GetPerimeter()
{
	return 0.0;
}

double Rectangle::GetSquare()
{
	return 0.0;
}

void Rectangle::Draw(sf::RenderWindow* window)
{
	window->draw(m_rectangle);
}

Rectangle::Rectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY)
{
	double width = bottomRightX - topLeftX;
	double height = bottomRightY - topLeftY;

	m_rectangle = sf::RectangleShape(sf::Vector2f(width, height));
	m_rectangle.setPosition(topLeftX, topLeftY);
}

sf::FloatRect Rectangle::GetGlobalBounds()
{
	return m_rectangle.getGlobalBounds();
}

void Rectangle::SetPosition(float x, float y)
{
	m_rectangle.setPosition(x, y);
}

sf::Vector2f Rectangle::GetOrigin()
{
	return m_rectangle.getOrigin();
}

bool Rectangle::IsSelected()
{
	return m_isSelected;
}

void Rectangle::Select()
{
	m_isSelected = true;
}

void Rectangle::UnSelect()
{
	m_isSelected = false;
}

void Rectangle::Move(float x, float y)
{
	m_rectangle.move(x, y);
}

bool Rectangle::IsPartOfCompound()
{
	return m_isPartOfCompound;
}

void Rectangle::SetIsPartOfCompound()
{
	m_isPartOfCompound = true;
}

void Rectangle::UnsetIsPartOfCompound()
{
	m_isPartOfCompound = false;
}
