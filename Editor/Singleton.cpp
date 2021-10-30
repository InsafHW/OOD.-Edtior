#include "Singleton.h"

Singleton& Singleton::GetInstance()
{
	static Singleton instance;
	return instance;
}

void Singleton::AddShape(CompoundShape* shape)
{
	m_shapes.push_back(shape);
}

void Singleton::PollEvents()
{
}

void Singleton::Update()
{
}

void Singleton::Render()
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(m_window);
	}
}

void Singleton::Start()
{
	m_window->setKeyRepeatEnabled(false);

	while (m_window->isOpen())
	{
		PollEvents();
		Update();
		m_window->clear();
		Render();
		m_window->display();
	}
}


