#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "CompoundShape.h"

class Canvas
{
public:
	Canvas(std::list<CompoundShape*> shapes)
		: m_shapes(shapes)
	{};

	void AddShape(CompoundShape* shape);
	void PollEvents(sf::Event event, sf::RenderWindow* window);
	void Update();
	void Draw(sf::RenderWindow* window);

	void SetDragAndDropState()
	{

	};

	void SetAddRectangleState()
	{

	};

	void SetAddCircleState()
	{

	};

	void SetAddTriangleState()
	{

	};

	void SetChangeFillColorState()
	{

	};

	void SetChangeOutlineColorState()
	{

	};

	void SetChangeOutlineThicknessState()
	{

	};

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

};
