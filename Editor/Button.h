#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Rectangle.h"
#include "ButtonType.h"

class Button : public Rectangle
{
public:
	Button(std::string texturePath, float topLeftX, float topLeftY, int buttonSize, ButtonType type);
	void Draw(sf::RenderWindow* window);
	void Select();
	void UnSelect();
	ButtonType GetButtonType();
private:
	sf::Texture* m_texture;
	sf::Sprite m_sprite;
	bool m_selected = false;
	ButtonType m_type;
};

