#pragma once
#include <vector>
#include <list>
#include "IShape.h"
#include <iostream>

const float INIT_MOUSE_POS = -100000;

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
		if (m_prevX != INIT_MOUSE_POS && m_prevY != INIT_MOUSE_POS)
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
	};

	bool IsMouseInGroup(float x, float y)
	{
		return GetGlobalBounds().contains(x, y);
	};

	sf::RectangleShape GetBorder()
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
	};

	sf::FloatRect GetGlobalBounds()
	{
		return GetBorder().getGlobalBounds();
	};

	sf::Vector2f GetOrigin()
	{
		return GetBorder().getOrigin();
	};

	bool IsSelected()
	{
		return m_selected;
	};

	void Select()
	{
		if (m_shapes.size() == 1)
		{
			m_shapes.back()->Select();
		}
		m_selected = true;
	}

	void Unselect()
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->UnSelect();
		}
		m_selected = false;
	}

	void ChangeFillColor(sf::Color color)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->ChangeFillColor(color);
		}
	}

	void ChangeOutlineColor(sf::Color color)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->ChangeOutlineColor(color);
		}
	}

	void ChangeOutlineThickness(int size)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->ChangeOutlineThickness(size);
		}
	}

	sf::Color GetFillColor()
	{
		return m_shapes.front()->GetFillColor();
	}
private:
	std::list<IShape*> m_shapes;
	float m_prevX = INIT_MOUSE_POS;
	float m_prevY = INIT_MOUSE_POS;
	bool m_selected = false;
};

