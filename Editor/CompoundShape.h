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
		std::cout << "x = " << x << "; y = " << y << std::endl;
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->SetPosition(x, y);
			//(*it)->SetPosition((*it)->GetGlobalBounds().left - x, (*it)->GetGlobalBounds().top - y);
		}
	};

	void Draw(sf::RenderWindow* window)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->Draw(window);
		}
	};

	bool IsMouseInGroup(float x, float y)
	{
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if ((*it)->GetGlobalBounds().contains(x, y)) {
				return true;
			};
		}
		return false;
	};

	sf::FloatRect GetGlobalBounds()
	{
		// find max left x and max right y
		int minX = 100000;
		int maxX = 0;
		int maxY = 0;
		int minY = 100000;

		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if ((*it)->GetGlobalBounds().left + (*it)->GetGlobalBounds().width > maxX)
			{
				maxX = (*it)->GetGlobalBounds().left + (*it)->GetGlobalBounds().width;
			}
			if ((*it)->GetGlobalBounds().left < minX)
			{
				minX = (*it)->GetGlobalBounds().left;
			}
			if ((*it)->GetGlobalBounds().top + (*it)->GetGlobalBounds().height > maxY)
			{
				maxY = (*it)->GetGlobalBounds().top + (*it)->GetGlobalBounds().height;
			}
			if ((*it)->GetGlobalBounds().top < minY)
			{
				minY = (*it)->GetGlobalBounds().top;
			}
		}

		sf::RectangleShape rect(sf::Vector2f(maxX - minX, maxY - minY));
		rect.setPosition(minX, minY);
		return rect.getGlobalBounds();
	};

	sf::Vector2f GetOrigin()
	{
		int minX = 100000;
		int maxX = 0;
		int maxY = 0;
		int minY = 100000;

		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if ((*it)->GetGlobalBounds().left + (*it)->GetGlobalBounds().width > maxX)
			{
				maxX = (*it)->GetGlobalBounds().left + (*it)->GetGlobalBounds().width;
			}
			if ((*it)->GetGlobalBounds().left < minX)
			{
				minX = (*it)->GetGlobalBounds().left;
			}
			if ((*it)->GetGlobalBounds().top + (*it)->GetGlobalBounds().height > maxY)
			{
				maxY = (*it)->GetGlobalBounds().top + (*it)->GetGlobalBounds().height;
			}
			if ((*it)->GetGlobalBounds().top < minY)
			{
				minY = (*it)->GetGlobalBounds().top;
			}
		}

		sf::RectangleShape rect(sf::Vector2f(maxX - minX, maxY - minY));
		rect.setPosition(minX, minY);
		return rect.getOrigin();
	};

private:
	std::list<IShape*> m_shapes;
};

