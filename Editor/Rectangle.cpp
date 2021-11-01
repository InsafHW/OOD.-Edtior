#include "Rectangle.h"

float Rectangle::GetPerimeter()
{
	const auto bounds = m_rectangle.getGlobalBounds();
	return (bounds.width + bounds.height) * 2;
}

float Rectangle::GetSquare()
{
	const auto bounds = m_rectangle.getGlobalBounds();
	return bounds.width * bounds.height;
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