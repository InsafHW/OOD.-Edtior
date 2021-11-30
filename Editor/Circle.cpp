#include "Circle.h"

float Circle::GetPerimeter()
{
	return 2 * M_PI * m_circle.getRadius();
}

float Circle::GetSquare()
{
	return M_PI * std::pow(m_circle.getRadius(), 2);
}

sf::Color Circle::GetFillColor()
{
	return m_circle.getFillColor();
}

void Circle::Draw(sf::RenderWindow* window)
{
	window->draw(m_circle);
}

Circle::Circle(double centerX, double centerY, double radius)
{
	m_circle = sf::CircleShape(radius);
	m_circle.setPosition(centerX, centerY);
	m_circle.setOutlineThickness(1);
	m_circle.setOutlineColor(sf::Color::Red);
}

sf::FloatRect Circle::GetGlobalBounds()
{
	return m_circle.getGlobalBounds();
}

sf::Vector2f Circle::GetOrigin()
{
	return m_circle.getOrigin();
}

bool Circle::IsSelected()
{
	return m_isSelected;
}

void Circle::Select()
{
	m_isSelected = true;
}

void Circle::UnSelect()
{
	m_isSelected = false;
}

void Circle::Move(float x, float y)
{
	m_circle.move(x, y);
}

void Circle::ChangeFillColor(sf::Color color)
{
	m_circle.setFillColor(color);
}

void Circle::ChangeOutlineColor(sf::Color color)
{
	m_circle.setOutlineColor(color);
}

void Circle::ChangeOutlineThickness(int size)
{
	m_circle.setOutlineThickness(size);
}

IShapeType Circle::GetType()
{
	return IShapeType::CIRCLE;
}
