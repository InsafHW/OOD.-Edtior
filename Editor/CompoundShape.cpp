#include "CompoundShape.h"

void CompoundShape::Add(IShape* child)
{
	m_shapes.push_back(child);
}

void CompoundShape::Remove(IShape* child)
{
	m_shapes.remove(child);
}

void CompoundShape::RemoveAll()
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		m_shapes.remove(*it);
	}
}

std::list<IShape*> CompoundShape::GetShapes()
{
	return m_shapes;
}

void CompoundShape::Move(float x, float y)
{

	if (x == m_prevX && y == m_prevY)
	{
		return;
	}
	if (m_prevX != INIT_MOUSE_POS && m_prevY != INIT_MOUSE_POS)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->Move(x - m_prevX, y - m_prevY);
		}
	}

	m_prevX = x;
	m_prevY = y;
}

void CompoundShape::Draw(sf::RenderWindow* window)
{
	if (m_shapes.size() > 1)
	{
		auto rect = GetBorder();
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color::Green);
		window->draw(rect);
	}
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(window);
	}
}

bool CompoundShape::IsMouseInGroup(float x, float y)
{
	return GetGlobalBounds().contains(x, y);
}

sf::RectangleShape CompoundShape::GetBorder()
{
	// find max left x and max right y
	float minX = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float minY = FLT_MAX;

	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		auto bounds = (*it)->GetGlobalBounds();
		maxX = std::max(bounds.left + bounds.width, maxX);
		minX = std::min(bounds.left, minX);
		maxY = std::max(bounds.top + bounds.height, maxY);
		minY = std::min(bounds.top, minY);
	}

	sf::RectangleShape rect(sf::Vector2f(maxX - minX, maxY - minY));
	rect.setPosition(minX, minY);
	return rect;
}

sf::FloatRect CompoundShape::GetGlobalBounds()
{
	return GetBorder().getGlobalBounds();
}

sf::Vector2f CompoundShape::GetOrigin()
{
	return GetBorder().getOrigin();
}

bool CompoundShape::IsSelected()
{
	return m_selected;
}

void CompoundShape::Select()
{
	if (m_shapes.size() == 1)
	{
		m_shapes.back()->Select();
	}
	m_selected = true;
}

void CompoundShape::Unselect()
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->UnSelect();
	}
	m_selected = false;
}

void CompoundShape::ChangeFillColor(sf::Color color)
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->ChangeFillColor(color);
	}
}

void CompoundShape::ChangeOutlineColor(sf::Color color)
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->ChangeOutlineColor(color);
	}
}

void CompoundShape::ChangeOutlineThickness(int size)
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->ChangeOutlineThickness(size);
	}
}

sf::Color CompoundShape::GetFillColor()
{
	return m_shapes.front()->GetFillColor();
}