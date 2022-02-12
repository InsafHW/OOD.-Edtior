#include "Decorator.h"

Decorator::Decorator(IShape* shape)
	:m_shape(shape)
{}

void Decorator::Draw(sf::RenderWindow* window)
{
	m_shape->Draw(window);
}

float Decorator::GetPerimeter()
{
	return m_shape->GetPerimeter();
}

float Decorator::GetSquare()
{
	return m_shape->GetSquare();
}

sf::FloatRect Decorator::GetGlobalBounds()
{
	return m_shape->GetGlobalBounds();
}

sf::Vector2f Decorator::GetOrigin()
{
	return m_shape->GetOrigin();
}

bool Decorator::IsSelected()
{
	return m_shape->IsSelected();
}

void Decorator::Select()
{
	m_shape->Select();
}

void Decorator::UnSelect()
{
	m_shape->UnSelect();
}

void Decorator::Move(float x, float y)
{
	m_shape->Move(x, y);
}

void Decorator::ChangeFillColor(sf::Color color)
{
	m_shape->ChangeFillColor(color);
}

void Decorator::ChangeOutlineColor(sf::Color color)
{
	m_shape->ChangeOutlineColor(color);
}

void Decorator::ChangeOutlineThickness(int size)
{
	m_shape->ChangeOutlineThickness(size);
}

sf::Color Decorator::GetFillColor()
{
	return m_shape->GetFillColor();
}

IShapeType Decorator::GetType()
{
	return m_shape->GetType();
}

sf::Color Decorator::GetOutlineColor()
{
	return m_shape->GetOutlineColor();
};