#include "AddTriangleState.h"

AddTriangleState::AddTriangleState(ICanvas& canvas)
	:m_canvas(canvas)
{};

void AddTriangleState::PollEvents(sf::Event event, sf::RenderWindow* window)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.y > 30)
		{
			CompoundShape* shape = new CompoundShape();
			m_canvas.PushInHistory();
			shape->Add(new OutlineDecorator(new Triangle(event.mouseButton.x, event.mouseButton.y + 100, event.mouseButton.x + 100, event.mouseButton.y, event.mouseButton.x + 200, event.mouseButton.y + 100)));
			m_canvas.AddShape(shape);
		};
		break;
	default:
		break;
	}
};