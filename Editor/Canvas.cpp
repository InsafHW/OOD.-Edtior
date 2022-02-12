#include "Canvas.h"

Canvas::Canvas(std::list<CompoundShape*> shapes)
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
	PushInHistory();
	SetSaveStrategy(std::make_unique<SaveBinaryStrategy>());
}

void Canvas::PollEvents(sf::Event event, sf::RenderWindow* window)
{
	m_state->PollEvents(event, window);
};

void Canvas::Update()
{
	if (m_draggingShape)
	{
		auto candidate = (*std::next(m_shapes.begin(), m_draggingShapeIdx));
		if (candidate)
		{
			if (candidate->GetShapes().size() == 1 && candidate->IsSelected() || candidate->GetShapes().size() > 1)
			{
				candidate->Move(m_mouseX - m_mouseShapeOffset.x, m_mouseY - m_mouseShapeOffset.y);
			}
		};
	}
}

void Canvas::Draw(sf::RenderWindow* window)
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		(*it)->Draw(window);
	}
}

void Canvas::AddShape(CompoundShape* shape)
{
	m_shapes.push_back(shape);
}

void Canvas::RemoveShape(CompoundShape* shape)
{
	m_shapes.remove(shape);
}

void Canvas::AddSelectedShape(CompoundShape* shape)
{
	m_selectedShapes.push_back(shape);
}

void Canvas::RemoveSelectedShape(CompoundShape* shape)
{
	m_selectedShapes.remove(shape);
};

sf::Color Canvas::GetSelectedColor()
{
	return m_color;
};

int Canvas::GetSelectedSize()
{
	return m_size;
}

std::list<CompoundShape*>& Canvas::GetShapes()
{
	return m_shapes;
}

std::list<CompoundShape*>& Canvas::GetSelectedShapes()
{
	return m_selectedShapes;
}

bool Canvas::IsMouseClicked()
{
	return m_mouseClicked;
}

bool Canvas::IsDraggingShape()
{
	return m_draggingShape;
}

bool Canvas::IsLShiftPressed()
{
	return m_lShiftPressed;
}

bool Canvas::IsCtrlPressed()
{
	return m_ctrlPressed;
}

sf::Vector2f Canvas::GetMouseShapeOffset()
{
	return m_mouseShapeOffset;
}
int Canvas::GetMouseX()
{
	return m_mouseX;
}

int Canvas::GetMouseY()
{
	return m_mouseY;
}

int Canvas::GetDraggingShapeIdx()
{
	return m_draggingShapeIdx;
}

void Canvas::SetIsMouseClicked(bool clicked)
{
	m_mouseClicked = clicked;
}

void Canvas::SetIsDragginShape(bool dragging)
{
	m_draggingShape = dragging;
}

void Canvas::SetIsLShiftPressed(bool pressed)
{
	m_lShiftPressed = pressed;
}

void Canvas::SetIsCtrlPressed(bool pressed)
{
	m_ctrlPressed = pressed;
}

void Canvas::SetMouseShapeOffset(sf::Vector2f offset)
{
	m_mouseShapeOffset = offset;
}

void Canvas::SetMouseX(int x)
{
	m_mouseX = x;
}

void Canvas::SetMouseY(int y)
{
	m_mouseY = y;
}

void Canvas::SetDraggingShapeIdx(int idx)
{
	m_draggingShapeIdx = idx;
}

void Canvas::SetDragAndDropState()
{
	m_state = &m_dragAndDropState;
}

void Canvas::SetAddRectangleState()
{
	m_state = &m_addRectangleState;
}

void Canvas::SetAddCircleState()
{
	m_state = &m_addCircleState;
}

void Canvas::SetAddTriangleState()
{
	m_state = &m_addTriangleState;
}

void Canvas::SetChangeFillColorState(sf::Color color)
{
	m_state = &m_changeFillColorState;
	m_color = color;
}

void Canvas::SetChangeOutlineColorState(sf::Color color)
{
	m_state = &m_changeOutlineColorState;
	m_color = color;
}

void Canvas::SetChangeOutlineThicknessState(int size)
{
	m_state = &m_changeOutlineThicknessState;
	m_size = size;
}

CanvasMemento Canvas::SaveState()
{
	std::cout << "Saving state..." << std::endl;
	return CanvasMemento(m_shapes, m_selectedShapes);
}

void Canvas::RestoreState()
{
	CanvasMemento memento = m_history.Pop();
	m_shapes.clear();
	m_selectedShapes.clear();
	for (auto it = memento.m_shapes.begin(); it != memento.m_shapes.end(); it++)
	{
		(*it).shape->ChangeFillColor((*it).fillColor);
		m_shapes.push_back((*it).shape);
	}

	m_selectedShapes = memento.m_selectedShapes;
}

void Canvas::PushInHistory()
{
	m_history.Push(SaveState());
}

void Canvas::SaveIntoFile()
{
	std::cout << "Saving into file..." << std::endl;
	m_saveStrategy->SaveFile(m_shapes);
}

void Canvas::SetSaveStrategy(std::unique_ptr<SaveStrategy>&& saveBehavior)
{
	m_saveStrategy = std::move(saveBehavior);
}

void Canvas::ReadFromTxt()
{
	m_shapes = m_txtReader.GetShapes();
}

void Canvas::ReadFromBin()
{
	m_shapes = m_binaryReader.GetShapes();
};

void Canvas::ClearAllSelectedShapes()
{
	m_selectedShapes.clear();
};
