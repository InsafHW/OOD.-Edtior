#pragma once
#include "IShape.h"
#include <iostream>

class OutlineDecorator : public IShape
{
public:
	double GetPerimeter() override
	{
		return 0;
	};
	double GetSquare() override
	{
		return 0;
	};
	void Draw(sf::RenderWindow* window) override
	{
		m_shape->Draw(window);

		if (m_shape->IsSelected() && !m_shape->IsPartOfCompound())
		{
			// draw outline
			sf::RectangleShape rect(sf::Vector2f(m_shape->GetGlobalBounds().width, m_shape->GetGlobalBounds().height));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineThickness(2);
			rect.setOutlineColor(sf::Color::Green);
			rect.setPosition(m_shape->GetGlobalBounds().left, m_shape->GetGlobalBounds().top);
			window->draw(rect);
		}
	};

	bool IsPartOfCompound() override
	{
		return m_shape->IsPartOfCompound();
	};

	void SetIsPartOfCompound() override
	{
		m_shape->SetIsPartOfCompound();
	};

	void UnsetIsPartOfCompound() override
	{
		m_shape->UnsetIsPartOfCompound();
	};

	OutlineDecorator(IShape* shape)
	{
		m_shape = shape;
	}
	sf::FloatRect GetGlobalBounds() override
	{
		return m_shape->GetGlobalBounds();
	};
	void SetPosition(float x, float y) override
	{
		m_shape->SetPosition(x, y);
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
private:
	IShape* m_shape;
};

