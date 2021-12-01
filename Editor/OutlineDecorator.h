#pragma once
#include "IShape.h"
#include <iostream>

const auto OUTLINE_COLOR = sf::Color::Green;
const int OUTLINE_THICKNESS = 2;

class OutlineDecorator : public IShape
{
public:
	float GetPerimeter() override
	{
		return 0;
	};
	float GetSquare() override
	{
		return 0;
	};
	void Draw(sf::RenderWindow* window) override
	{
		m_shape->Draw(window);

		if (m_shape->IsSelected())
		{
			// draw outline
			sf::RectangleShape rect(sf::Vector2f(m_shape->GetGlobalBounds().width, m_shape->GetGlobalBounds().height));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(OUTLINE_THICKNESS);
			rect.setOutlineColor(OUTLINE_COLOR);
			rect.setPosition(m_shape->GetGlobalBounds().left, m_shape->GetGlobalBounds().top);
			window->draw(rect);
		}
	};

	OutlineDecorator(IShape* shape)
	{
		m_shape = shape;
	}

	sf::FloatRect GetGlobalBounds() override
	{
		return m_shape->GetGlobalBounds();
	};

	sf::Vector2f GetOrigin() override
	{
		return m_shape->GetOrigin();
	};
	bool IsSelected() override
	{
		return m_shape->IsSelected();
	};
	void Select() override
	{
		m_shape->Select();
	};
	void UnSelect() override
	{
		m_shape->UnSelect();
	};
	void Move(float x, float y) override
	{
		m_shape->Move(x, y);
	}
	void ChangeFillColor(sf::Color color) override
	{
		m_shape->ChangeFillColor(color);
	}
	void ChangeOutlineColor(sf::Color color) override
	{
		m_shape->ChangeOutlineColor(color);
	}
	void ChangeOutlineThickness(int size) override
	{
		m_shape->ChangeOutlineThickness(size);
	}
	sf::Color GetFillColor() override
	{
		return m_shape->GetFillColor();
	};

	IShapeType GetType() override
	{
		return m_shape->GetType();
	};
	sf::Color GetOutlineColor() override
	{
		return m_shape->GetOutlineColor();
	};
private:
	IShape* m_shape;
};

