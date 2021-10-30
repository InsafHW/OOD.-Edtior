#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "IShape.h"
#include "CompoundShape.h"
#include "OutlineDecorator.h"
#include "Circle.h"
#include "Rectangle.h"

class Singleton
{
public:
	static Singleton& GetInstance();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void AddShape(CompoundShape* shape);

	void Start();

private:
	Singleton();
	sf::RenderWindow* m_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Editor");

	std::list<CompoundShape*> m_shapes;

	bool mouseClicked = false;
	bool draggingShape = false;
	bool draggingCompound = false;
	bool lShiftPressed = false;
	bool ctrlPressed = false;

	sf::Vector2f mouseShapeOffset;

	int mouseX = 0;
	int mouseY = 0;

	int draggingShapeIdx = 0;

	void PollEvents();
	void Update();
	void Render();
};
