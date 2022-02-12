#pragma once
#include "Canvas.h"
#include "Toolbar.h"

class Editor
{
public:
	static Editor& GetInstance(std::list<CompoundShape*> shapes);
	Editor(const Editor&) = delete;
	Editor& operator=(const Editor&) = delete;

	void Start();
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

