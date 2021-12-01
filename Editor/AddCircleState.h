#pragma once
#include "IState.h"
#include "Circle.h"

class AddCircleState : public IState
{
public:
	AddCircleState(ICanvas& canvas)
		:m_canvas(canvas)
	{};

	void PollEvents(sf::Event event, sf::RenderWindow* window) override
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.y > 30)
			{
				CompoundShape* shape = new CompoundShape();
				m_canvas.PushInHistory();
				shape->Add(new OutlineDecorator(new Circle(event.mouseButton.x, event.mouseButton.y, 100)));
				m_canvas.AddShape(shape);
			};
			break;
		default:
			break;
		}
	};

private:
	ICanvas& m_canvas;
};

