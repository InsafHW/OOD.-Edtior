#pragma once
#include "Canvas.h"
#include "Toolbar.h"

class Application
{
public:
	static Application& GetInstance(std::list<CompoundShape*> shapes)
	{
		static Application instance(shapes);
		return instance;
	};
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void Start()
	{
		while (m_window->isOpen())
		{
			while (m_window->pollEvent(m_event))
			{
				if (m_event.type == sf::Event::Closed)
				{
					m_window->close();
				}

				m_toolbar->PollEventAndUpdate(m_event, m_window);
				m_canvas->PollEvents(m_event, m_window);
			}
			m_canvas->Update();

			m_window->clear();

			m_toolbar->Draw(m_window);
			m_canvas->Draw(m_window);

			m_window->display();
		}
	};

private:
	Application(std::list<CompoundShape*> shapes)
	{
		m_canvas = new Canvas(shapes);
		m_canvas->SetDragAndDropStateMan();
		m_toolbar = new Toolbar(m_canvas);
		m_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Editor");
	};

	Canvas* m_canvas;
	Toolbar* m_toolbar;
	sf::RenderWindow* m_window;
	sf::Event m_event;
};

