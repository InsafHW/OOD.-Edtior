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
private:
	std::list<IShape*> m_shapes;
};

