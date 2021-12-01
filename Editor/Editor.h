#pragma once
#include "Canvas.h"
#include "Toolbar.h"

class Editor
{
public:
	static Editor& GetInstance(std::list<CompoundShape*> shapes)
	{
		static Editor instance(shapes);
		return instance;
	};
	Editor(const Editor&) = delete;
	Editor& operator=(const Editor&) = delete;

	void Start()
	{
		while (m_window->isOpen())
		{
			while (m_window->pollEvent(m_event))
			{
				if (m_event.type == sf::Event::Closed)
				{
					m_window->close();
					m_canvas->SaveIntoFile();
				}

				m_toolbar->PollEventAndUpdate(m_event, m_window);
				m_canvas->PollEvents(m_event, m_window);
			}
			m_canvas->Update();

			m_window->clear();

			m_canvas->Draw(m_window);
			m_toolbar->Draw(m_window);

			m_window->display();
		}
	};

private:
	Editor(std::list<CompoundShape*> shapes)
	{
		m_canvas = new Canvas(shapes);
		m_toolbar = new Toolbar(m_canvas);
		m_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Editor");
	};

	Canvas* m_canvas;
	Toolbar* m_toolbar;
	sf::RenderWindow* m_window;
	sf::Event m_event;
};

