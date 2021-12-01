#pragma once
#include "CompoundShape.h"
#include "SaveStrategy.h"
#include <list>



struct ICanvas
{
	virtual void PollEvents(sf::Event event, sf::RenderWindow* window) = 0;
	virtual void PushInHistory() = 0;
	virtual void AddShape(CompoundShape* shape) = 0;
	virtual void RemoveShape(CompoundShape* shape) = 0;
	virtual void AddSelectedShape(CompoundShape* shape) = 0;
	virtual void RemoveSelectedShape(CompoundShape* shape) = 0;

	virtual bool IsMouseClicked() = 0;
	virtual bool IsDragginShape() = 0;
	virtual bool IsLShiftPressed() = 0;
	virtual bool IsCtrlPressed() = 0;
	virtual sf::Vector2f GetMouseShapeOffset() = 0;
	virtual int GetMouseX() = 0;
	virtual int GetMouseY() = 0;
	virtual int GetDraggingShapeIdx() = 0;

	virtual void SetIsMouseClicked(bool clicked) = 0;
	virtual void SetIsDragginShape(bool dragging) = 0;
	virtual void SetIsLShiftPressed(bool pressed) = 0;
	virtual void SetIsCtrlPressed(bool pressed) = 0;
	virtual void SetMouseShapeOffset(sf::Vector2f offset) = 0;
	virtual void SetMouseX(int x) = 0;
	virtual void SetMouseY(int y) = 0;
	virtual void SetDraggingShapeIdx(int idx) = 0;

	virtual std::list<CompoundShape*>& GetShapes() = 0;
	virtual std::list<CompoundShape*>& GetSelectedShapes() = 0;
	virtual void RestoreState() = 0;
	virtual void SetSaveStrategy(std::unique_ptr<SaveStrategy>&& saveBehavior) = 0;
	virtual void SaveIntoFile() = 0;

	virtual sf::Color GetSelectedColor() = 0;
	virtual int GetSelectedSize() = 0;

	virtual void ClearAllSelectedShapes() = 0;
};

