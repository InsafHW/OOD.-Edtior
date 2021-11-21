#include "Triangle.h"

float Triangle::GetPerimeter()
{
	return m_AB + m_BC + m_AC;
}

float Triangle::GetSquare()
{
	float poluperimeter = (m_AB + m_BC + m_AC) / 2;
	return sqrt(poluperimeter * (poluperimeter - m_AB) * (poluperimeter - m_AC) * (poluperimeter - m_BC));
}

void Triangle::Draw(sf::RenderWindow* window)
{
	window->draw(m_triangle);
}

Triangle::Triangle(double aX, double aY, double bX, double bY, double cX, double cY)
{
	m_triangle.setPointCount(3);
	m_triangle.setPoint(0, sf::Vector2f(aX, aY));
	m_triangle.setPoint(1, sf::Vector2f(bX, bY));
	m_triangle.setPoint(2, sf::Vector2f(cX, cY));

	m_AB = sqrt(pow(bX - aX, 2) + pow(bY - aY, 2));
	m_BC = sqrt(pow(cX - bX, 2) + pow(cY - bY, 2));
	m_AC = sqrt(pow(cX - aX, 2) + pow(cY - aY, 2));
}

sf::FloatRect Triangle::GetGlobalBounds()
{
	return m_triangle.getGlobalBounds();
}

sf::Vector2f Triangle::GetOrigin()
{
	return m_triangle.getOrigin();
}

bool Triangle::IsSelected()
{
	return m_isSelected;
}

void Triangle::Select()
{
	m_isSelected = true;
}

void Triangle::UnSelect()
{
	m_isSelected = false;
}

void Triangle::Move(float x, float y)
{
	m_triangle.move(x, y);
}

void Triangle::ChangeFillColor(sf::Color color)
{
	m_triangle.setFillColor(color);
}

void Triangle::ChangeOutlineColor(sf::Color color)
{
	m_triangle.setOutlineColor(color);
}

void Triangle::ChangeOutlineThickness(int size)
{
	m_triangle.setOutlineThickness(size);
}
