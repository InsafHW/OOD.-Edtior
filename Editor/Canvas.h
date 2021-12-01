#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "CanvasState.h"
#include "CompoundShape.h"
#include "DragAndDropState.h"
#include "StateType.h"
#include "OutlineDecorator.h"
#include "Rectangle.h"
#include <fstream>
#include "Triangle.h"
#include "Circle.h"
#include <vector>
#include "BinaryReader.h"
#include "SaveStrategy.h"
#include "SaveBinaryStrategy.h"
#include "SaveTxtStrategy.h"
#include "TxtReader.h"

struct ShapeState
{
	CompoundShape* shape;
	sf::Color fillColor;
};

class CanvasMemento
{
public:
	std::list<ShapeState> m_shapes;
	std::list<CompoundShape*> m_selectedShapes;

	CanvasMemento(std::list<CompoundShape*> shapes, std::list<CompoundShape*> selectedShapes)
		:m_selectedShapes(selectedShapes)
	{
		for (auto it = shapes.begin(); it != shapes.end(); it++)
		{
			m_shapes.push_back({ *it, (*it)->GetFillColor() });
		}
	};
};

class CanvasHistory
{
public:
	CanvasHistory()
	{
	};

	void Push(CanvasMemento memento)
	{
		m_history.push_back(memento);
	};

	CanvasMemento Pop()
	{
		auto last = m_history[m_history.size() - 1];
		if (m_history.size() > 1)
		{
			m_history.pop_back();
		}
		return last;
	};
private:
	std::vector<CanvasMemento> m_history;
};

class Canvas
{
public:
	Canvas(std::list<CompoundShape*> shapes)
		: m_shapes(shapes),
		m_type(StateType::DRAG_AND_DROP)
	{
		m_history.Push(SaveState());
		SetSaveStrategy(std::make_unique<SaveBinaryStrategy>());
		//SetDragAndDropStateMan();
	}

	void PollEvents(sf::Event event, sf::RenderWindow* window)
	{
		switch (m_type)
		{
		case StateType::DRAG_AND_DROP:
			DragAndDropPollEvent(event, window);
			break;
		case StateType::ADD_RECTANGLE_TYPE:
			AddRectanglePollEvent(event, window);
			break;
		case StateType::ADD_TRIANGLE_TYPE:
			AddTrianglePollEvent(event, window);
			break;
		case StateType::ADD_CIRCLE_TYPE:
			AddCirclePollEvent(event, window);
			break;
		case StateType::CHAGNE_FILL_COLOR_TYPE:
			ChangeFillColorPollEvent(event, window);
			break;
		case StateType::CHANGE_OUTLINE_COLOR_TYPE:
			ChangeOutlineColorPollEvent(event, window);
			break;
		case StateType::CHANGE_OUTLINE_THICKNESS_TYPE:
			ChangeOutlineThicknessPollEvent(event, window);
			break;
		default:
			break;
		}
	};
	void Update();
	void Draw(sf::RenderWindow* window);

	void SetDragAndDropState()
	{
		m_type = StateType::DRAG_AND_DROP;
	};

	void SetAddRectangleState()
	{
		m_type = StateType::ADD_RECTANGLE_TYPE;
	};

	void SetAddCircleState()
	{
		m_type = StateType::ADD_CIRCLE_TYPE;
	};

	void SetAddTriangleState()
	{
		m_type = StateType::ADD_TRIANGLE_TYPE;
	};

	void SetChangeFillColorState(sf::Color color)
	{
		m_color = color;
		m_type = StateType::CHAGNE_FILL_COLOR_TYPE;
	};

	void SetChangeOutlineColorState(sf::Color color)
	{
		m_color = color;
		m_type = StateType::CHANGE_OUTLINE_COLOR_TYPE;
	};

	void SetChangeOutlineThicknessState(int size)
	{
		m_size = size;
		m_type = StateType::CHANGE_OUTLINE_THICKNESS_TYPE;
	};


	CanvasMemento SaveState()
	{
		std::cout << "Saving state..." << std::endl;
		return CanvasMemento(m_shapes, m_selectedShapes);
	};

	void RestoreState(CanvasMemento memento)
	{
		m_shapes.clear();
		for (auto it = memento.m_shapes.begin(); it != memento.m_shapes.end(); it++)
		{
			(*it).shape->ChangeFillColor((*it).fillColor);
			m_shapes.push_back((*it).shape);

		}

		m_selectedShapes = memento.m_selectedShapes;
	};

	void SaveIntoFile()
	{
		std::cout << "Saving into file..." << std::endl;
		m_saveStrategy->SaveFile(m_shapes);
	};

	void SetSaveStrategy(std::unique_ptr<SaveStrategy>&& saveBehavior)
	{
		m_saveStrategy = std::move(saveBehavior);
	};

	void ReadFromTxt()
	{
		m_shapes = m_txtReader.GetShapes();
	};

	void ReadFromBin()
	{
		m_shapes = m_binaryReader.GetShapes();
	};

private:
	StateType m_type;
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

	sf::Color m_color;
	int m_size;

	CanvasHistory m_history;
	BinaryReader m_binaryReader;
	TxtReader m_txtReader;

	std::unique_ptr<SaveStrategy> m_saveStrategy;

	void DragAndDropPollEvent(sf::Event event, sf::RenderWindow* window);
	void AddRectanglePollEvent(sf::Event event, sf::RenderWindow* window);
	void AddTrianglePollEvent(sf::Event event, sf::RenderWindow* window);
	void AddCirclePollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeFillColorPollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeOutlineColorPollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeOutlineThicknessPollEvent(sf::Event event, sf::RenderWindow* window);
};