#include "Editor.h"

Editor& Editor::GetInstance(std::list<CompoundShape*> shapes)
{
	static Editor instance(shapes);
	return instance;
}

void Editor::Start()
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