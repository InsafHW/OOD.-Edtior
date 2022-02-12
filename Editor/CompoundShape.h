#pragma once
#include <vector>
#include <list>
#include "IShape.h"
#include <iostream>

const float INIT_MOUSE_POS = -100000;

class CompoundShape
{
public:
	void Add(IShape* child);
	void Remove(IShape* child);
	void RemoveAll();
	std::list<IShape*> GetShapes();
	void Move(float x, float y);
	void Draw(sf::RenderWindow* window);
	bool IsMouseInGroup(float x, float y);
	sf::RectangleShape GetBorder();
	sf::FloatRect GetGlobalBounds();
	sf::Vector2f GetOrigin();
	bool IsSelected();
	void Select();
	void Unselect();
	void ChangeFillColor(sf::Color color);
	void ChangeOutlineColor(sf::Color color);
	void ChangeOutlineThickness(int size);
	sf::Color GetFillColor();
private:
	std::list<IShape*> m_shapes;
	float m_prevX = INIT_MOUSE_POS;
	float m_prevY = INIT_MOUSE_POS;
	bool m_selected = false;
};

