#include "ChangeOutlineColorState.h"

ChangeOutlineColorState::ChangeOutlineColorState(ICanvas& canvas)
	:m_canvas(canvas)
{};

void ChangeOutlineColorState::PollEvents(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			auto shapes = m_canvas.GetShapes();
			for (auto it = shapes.begin(); it != shapes.end(); it++)
			{
				if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					m_canvas.PushInHistory();
					(*it)->ChangeOutlineColor(m_canvas.GetSelectedColor());
					break;
				}
			}
		};
		break;
	default:
		break;
	}
};