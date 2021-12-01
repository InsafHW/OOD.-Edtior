#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "CanvasState.h"
#include "CompoundShape.h"
#include "DragAndDropState.h"
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
#include "IState.h"
#include "AddCircleState.h"
#include "AddRectangleState.h"
#include "DragAndDropState.h"
#include "AddTriangleState.h"
#include "ICanvas.h"
#include "ChangeFillColorState.h"
#include "ChangeOutlineColorState.h"
#include "ChangeOutlineThicknessState.h"

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

class Canvas : public ICanvas
{
public:
	Canvas(std::list<CompoundShape*> shapes)
		: m_shapes(shapes),
		m_state(&m_dragAndDropState),
		m_addCircleState(*this),
		m_addRectangleState(*this),
		m_dragAndDropState(*this),
		m_addTriangleState(*this),
		m_changeFillColorState(*this),
		m_changeOutlineColorState(*this),
		m_changeOutlineThicknessState(*this)
	{
		m_history.Push(SaveState());
		SetSaveStrategy(std::make_unique<SaveBinaryStrategy>());
	}

	void PollEvents(sf::Event event, sf::RenderWindow* window) override
	{
		m_state->PollEvents(event, window);
	};
	void Update();

	void Draw(sf::RenderWindow* window);

	void SetDragAndDropState()
	{
		m_state = &m_dragAndDropState;
	};

	void SetAddRectangleState()
	{
		m_state = &m_addRectangleState;
	};

	void SetAddCircleState()
	{
		m_state = &m_addCircleState;
	};

	void SetAddTriangleState()
	{
		m_state = &m_addTriangleState;
	};

	void SetChangeFillColorState(sf::Color color)
	{
		m_state = &m_changeFillColorState;
		m_color = color;
	};

	void SetChangeOutlineColorState(sf::Color color)
	{
		m_state = &m_changeOutlineColorState;
		m_color = color;
	};

	void SetChangeOutlineThicknessState(int size)
	{
		m_state = &m_changeOutlineThicknessState;
		m_size = size;
	};


	CanvasMemento SaveState()
	{
		std::cout << "Saving state..." << std::endl;
		return CanvasMemento(m_shapes, m_selectedShapes);
	};

	void RestoreState() override
	{
		CanvasMemento memento = m_history.Pop();
		m_shapes.clear();
		for (auto it = memento.m_shapes.begin(); it != memento.m_shapes.end(); it++)
		{
			(*it).shape->ChangeFillColor((*it).fillColor);
			m_shapes.push_back((*it).shape);

		}

		m_selectedShapes = memento.m_selectedShapes;
	};

	void SaveIntoFile() override
	{
		std::cout << "Saving into file..." << std::endl;
		m_saveStrategy->SaveFile(m_shapes);
	};

	void SetSaveStrategy(std::unique_ptr<SaveStrategy>&& saveBehavior) override
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

	void PushInHistory() override
	{
		m_history.Push(SaveState());
	};

	void AddShape(CompoundShape* shape) override
	{
		m_shapes.push_back(shape);
	};

	void RemoveShape(CompoundShape* shape) override
	{
		m_shapes.remove(shape);
	};

	void AddSelectedShape(CompoundShape* shape) override
	{
		m_selectedShapes.push_back(shape);
	};

	void RemoveSelectedShape(CompoundShape* shape) override
	{
		m_selectedShapes.remove(shape);
	};


	std::list<CompoundShape*>& GetShapes() override
	{
		return m_shapes;
	};
	std::list<CompoundShape*>& GetSelectedShapes() override
	{
		return m_selectedShapes;
	};

	bool IsMouseClicked() override
	{
		return m_mouseClicked;
	};

	bool IsDragginShape() override
	{
		return m_draggingShape;
	};
	bool IsLShiftPressed() override
	{
		return m_lShiftPressed;
	};
	bool IsCtrlPressed() override
	{
		return m_ctrlPressed;
	};

	sf::Vector2f GetMouseShapeOffset() override
	{
		return m_mouseShapeOffset;
	};
	int GetMouseX() override
	{
		return m_mouseX;
	};
	int GetMouseY() override
	{
		return m_mouseY;
	};
	int GetDraggingShapeIdx() override
	{
		return m_draggingShapeIdx;
	};

	void SetIsMouseClicked(bool clicked) override
	{
		m_mouseClicked = clicked;
	};
	void SetIsDragginShape(bool dragging) override
	{
		m_draggingShape = dragging;
	};
	void SetIsLShiftPressed(bool pressed) override
	{
		m_lShiftPressed = pressed;
	};
	void SetIsCtrlPressed(bool pressed) override
	{
		m_ctrlPressed = pressed;
	};
	void SetMouseShapeOffset(sf::Vector2f offset) override
	{
		m_mouseShapeOffset = offset;
	};
	void SetMouseX(int x) override
	{
		m_mouseX = x;
	};
	void SetMouseY(int y) override
	{
		m_mouseY = y;
	};
	void SetDraggingShapeIdx(int idx) override
	{
		m_draggingShapeIdx = idx;
	};

	sf::Color GetSelectedColor() override
	{
		return m_color;
	};

	int GetSelectedSize() override
	{
		return m_size;
	};

	void ClearAllSelectedShapes() override
	{
		m_selectedShapes.clear();
	};

private:
	std::list<CompoundShape*> m_shapes;
	std::list<CompoundShape*> m_selectedShapes;

	sf::Color m_color;
	int m_size;

	CanvasHistory m_history;
	BinaryReader m_binaryReader;
	TxtReader m_txtReader;

	std::unique_ptr<SaveStrategy> m_saveStrategy;

	DragAndDropState m_dragAndDropState;
	AddCircleState m_addCircleState;
	AddRectangleState m_addRectangleState;
	AddTriangleState m_addTriangleState;
	ChangeFillColorState m_changeFillColorState;
	ChangeOutlineColorState m_changeOutlineColorState;
	ChangeOutlineThicknessState m_changeOutlineThicknessState;

	IState* m_state;

	bool m_mouseClicked = false;
	bool m_draggingShape = false;
	bool m_lShiftPressed = false;
	bool m_ctrlPressed = false;
	sf::Vector2f m_mouseShapeOffset;
	int m_mouseX = 0;
	int m_mouseY = 0;
	int m_draggingShapeIdx = 0;
};