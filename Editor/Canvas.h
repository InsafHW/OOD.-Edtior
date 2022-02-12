#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "CanvasState.h"
#include "CompoundShape.h"
#include "DragAndDropState.h"
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
#include "CanvasHistory.h"

class Canvas : public ICanvas
{
public:
	Canvas(std::list<CompoundShape*> shapes);
	void PollEvents(sf::Event event, sf::RenderWindow* window) override;
	void Update();
	void Draw(sf::RenderWindow* window);
	void AddShape(CompoundShape* shape) override;
	void RemoveShape(CompoundShape* shape) override;
	void AddSelectedShape(CompoundShape* shape) override;
	void RemoveSelectedShape(CompoundShape* shape) override;
	void ClearAllSelectedShapes() override;

	// Getters
	sf::Color GetSelectedColor() override;
	int GetSelectedSize() override;
	std::list<CompoundShape*>& GetShapes() override;
	std::list<CompoundShape*>& GetSelectedShapes() override;
	bool IsMouseClicked() override;
	bool IsDraggingShape() override;
	bool IsLShiftPressed() override;
	bool IsCtrlPressed() override;
	sf::Vector2f GetMouseShapeOffset() override;
	int GetMouseX() override;
	int GetMouseY() override;
	int GetDraggingShapeIdx() override;

	// Setters
	void SetIsMouseClicked(bool clicked) override;
	void SetIsDragginShape(bool dragging) override;
	void SetIsLShiftPressed(bool pressed) override;
	void SetIsCtrlPressed(bool pressed) override;
	void SetMouseShapeOffset(sf::Vector2f offset) override;
	void SetMouseX(int x) override;
	void SetMouseY(int y) override;
	void SetDraggingShapeIdx(int idx) override;

	// States
	void SetDragAndDropState();
	void SetAddRectangleState();
	void SetAddCircleState();
	void SetAddTriangleState();
	void SetChangeFillColorState(sf::Color color);
	void SetChangeOutlineColorState(sf::Color color);
	void SetChangeOutlineThicknessState(int size);

	// Shapshots
	CanvasMemento SaveState();
	void RestoreState() override;
	void PushInHistory() override;

	// Files
	void SaveIntoFile() override;
	void SetSaveStrategy(std::unique_ptr<SaveStrategy>&& saveBehavior) override;
	void ReadFromTxt();
	void ReadFromBin();
private:
	std::list<CompoundShape*> m_shapes;
	std::list<CompoundShape*> m_selectedShapes;

	sf::Color m_color;
	int m_size;
	bool m_mouseClicked = false;
	bool m_draggingShape = false;
	bool m_lShiftPressed = false;
	bool m_ctrlPressed = false;
	sf::Vector2f m_mouseShapeOffset;
	int m_mouseX = 0;
	int m_mouseY = 0;
	int m_draggingShapeIdx = 0;

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
};