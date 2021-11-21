#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Rectangle.h"
#include "ButtonType.h"

class Button : public Rectangle
{
public:
	Button(std::string texturePath, float topLeftX, float topLeftY, int buttonSize, ButtonType type)
		:Rectangle(topLeftX, topLeftY, topLeftX + buttonSize, topLeftY + buttonSize),
		m_type(type)
	{
		m_texture = new sf::Texture();
		m_texture->loadFromFile(texturePath);
		m_sprite.setTexture(*m_texture);
		m_sprite.setPosition(topLeftX, topLeftY);
		m_selected = type == ButtonType::DRAG_AND_DROP;
	};

	void Draw(sf::RenderWindow* window)
	{
		if (m_selected)
		{
			auto globalBounds = m_sprite.getGlobalBounds();
			sf::RectangleShape outline(sf::Vector2f(globalBounds.width, globalBounds.height));
			outline.setPosition(globalBounds.left, globalBounds.top);
			outline.setFillColor(sf::Color::Transparent);
			outline.setOutlineColor(sf::Color::Green);
			outline.setOutlineThickness(5);
			window->draw(outline);
		};
		window->draw(m_sprite);
	};

	void Select()
	{
		m_selected = true;
	};

	void UnSelect()
	{
		m_selected = false;
	};

	ButtonType GetButtonType()
	{
		return m_type;
	};
private:
	sf::Texture* m_texture;
	sf::Sprite m_sprite;
	bool m_selected = false;
	ButtonType m_type;
};

