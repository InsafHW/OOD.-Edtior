#include "OutlineDecorator.h"

OutlineDecorator::OutlineDecorator(IShape* shape)
	: Decorator(shape)
{};

void OutlineDecorator::Draw(sf::RenderWindow* window)
{
	if (m_shape->IsSelected())
	{
		sf::RectangleShape rect(sf::Vector2f(m_shape->GetGlobalBounds().width, m_shape->GetGlobalBounds().height));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(OUTLINE_THICKNESS);
		rect.setOutlineColor(OUTLINE_COLOR);
		rect.setPosition(m_shape->GetGlobalBounds().left, m_shape->GetGlobalBounds().top);
		window->draw(rect);
	}
	Decorator::Draw(window);
}