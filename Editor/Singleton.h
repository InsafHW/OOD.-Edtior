#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "IShape.h"
#include "CompoundShape.h"
#include "OutlineDecorator.h"
#include "Circle.h"
#include "Rectangle.h"
#include <memory>

class Singleton
{
public:
	static Singleton& GetInstance(std::list<CompoundShape*> shapes);
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void Start();
private:
	Singleton(std::list<CompoundShape*> shapes) : m_shapes(shapes) {};
	sf::RenderWindow* m_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Editor");
	sf::Event m_event;
	sf::Vector2f m_mouseShapeOffset;

	std::list<CompoundShape*> m_shapes;
	std::list<CompoundShape*> m_selectedShapes;

	bool m_mouseClicked = false;
	bool m_draggingShape = false;
	bool m_lShiftPressed = false;
	bool m_ctrlPressed = false;

	int m_mouseX = 0;
	int m_mouseY = 0;
	int m_draggingShapeIdx = 0;

	void AddShape(CompoundShape* shape);
	void PollEvents();
	void Update();
	void Render();
};
