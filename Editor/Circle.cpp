#include "Circle.h"

double Circle::GetPerimeter()
{
	return 0.0;
}

double Circle::GetSquare()
{
	return 0.0;
}

void Circle::Draw(sf::RenderWindow* window)
{
	window->draw(m_circle);
}

Circle::Circle(double centerX, double centerY, double radius)
{
	m_circle = sf::CircleShape(radius);
	m_circle.setPosition(centerX, centerY);
}

sf::FloatRect Circle::GetGlobalBounds()
{
	return m_circle.getGlobalBounds();
}

void Circle::SetPosition(float x, float y)
{
	m_circle.setPosition(x, y);
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

bool Circle::IsPartOfCompound()
{
	return m_isPartOfCompound;
}

void Circle::SetIsPartOfCompound()
{
	m_isPartOfCompound = true;
}

void Circle::UnsetIsPartOfCompound()
{
	m_isPartOfCompound = false;
}
