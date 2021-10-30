#pragma once
#include <vector>
#include <list>
#include "IShape.h"
#include <iostream>

class CompoundShape
{
public:
	void Add(IShape* child)
	{
		m_shapes.push_back(child);
	}

	void Remove(IShape* child)
	{
		m_shapes.remove(child);
	}

	void RemoveAll()
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			m_shapes.remove(*it);
		}
	};

	std::list<IShape*> GetShapes()
	{
		return m_shapes;
	};

	void Move(float x, float y)
	{

		if (x == m_prevX && y == m_prevY)
		{
			return;
		}
		if (m_prevX != -100000 && m_prevY != -100000)
		{
			for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
			{
				(*it)->Move(x - m_prevX, y - m_prevY);
			}
		}

		m_prevX = x;
		m_prevY = y;
	};

	void Draw(sf::RenderWindow* window)
	{
		auto rect = GetBorder();
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color::Green);
		window->draw(rect);
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->Draw(window);
		}
	};

	bool IsMouseInGroup(float x, float y)
	{
		return GetGlobalBounds().contains(x, y);
	};

	sf::RectangleShape GetBorder()
	{
		// find max left x and max right y

		int minX = 100000;
		int maxX = 0;
		int maxY = 0;
		int minY = 100000;

		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			auto bounds = (*it)->GetGlobalBounds();
			if (bounds.left + bounds.width > maxX)
			{
				maxX = bounds.left + bounds.width;
			}
			if (bounds.left < minX)
			{
				minX = bounds.left;
			}
			if (bounds.top + bounds.height > maxY)
			{
				maxY = bounds.top + bounds.height;
			}
			if (bounds.top < minY)
			{
				minY = bounds.top;
			}
		}

		sf::RectangleShape rect(sf::Vector2f(maxX - minX, maxY - minY));
		rect.setPosition(minX, minY);
		return rect;
	};

	sf::FloatRect GetGlobalBounds()
	{
		return GetBorder().getGlobalBounds();
	};

	sf::Vector2f GetOrigin()
	{
		return GetBorder().getOrigin();
	};

private:
	std::list<IShape*> m_shapes;
	float m_prevX = -100000;
	float m_prevY = -100000;
};

