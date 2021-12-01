#pragma once
#include "IState.h"
#include "SaveBinaryStrategy.h"
#include "SaveTxtStrategy.h"

class DragAndDropState : public IState
{
public:
	DragAndDropState(ICanvas& canvas)
		:m_canvas(canvas)
	{};

	void PollEvents(sf::Event event, sf::RenderWindow* window) override
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (m_canvas.IsCtrlPressed() && event.key.code == sf::Keyboard::Z)
			{
				m_canvas.RestoreState();
			};
			if (event.key.code == sf::Keyboard::LShift)
			{
				m_canvas.SetIsLShiftPressed(true);
			}
			if (event.key.code == sf::Keyboard::LControl)
			{
				m_canvas.SetIsCtrlPressed(true);
			};
			if (m_canvas.IsCtrlPressed() && event.key.code == sf::Keyboard::G && m_canvas.GetSelectedShapes().size() > 1)
			{
				CompoundShape* comp = new CompoundShape();
				auto selectedShapes = m_canvas.GetSelectedShapes();

				for (auto it = selectedShapes.begin(); it != selectedShapes.end(); it++)
				{
					auto shapes = (*it)->GetShapes();
					for (auto innerIt = shapes.begin(); innerIt != shapes.end(); innerIt++)
					{
						comp->Add(*innerIt);
						(*innerIt)->UnSelect();
					}
					m_canvas.RemoveShape(*it);
					delete* it;
				}
				m_canvas.AddShape(comp);
				m_canvas.ClearAllSelectedShapes();
				m_canvas.AddSelectedShape(comp);
				m_canvas.SetDraggingShapeIdx(m_canvas.GetShapes().size() - 1);
			}
			if (m_canvas.IsCtrlPressed() && event.key.code == sf::Keyboard::U)
			{
				auto compound = *std::next(m_canvas.GetShapes().begin(), m_canvas.GetDraggingShapeIdx());
				auto shapes = compound->GetShapes();
				if (shapes.size() > 1)
				{
					for (auto it = shapes.begin(); it != shapes.end(); it++)
					{
						CompoundShape* soloShape = new CompoundShape();
						soloShape->Add(*it);
						soloShape->Select();
						m_canvas.AddShape(soloShape);
						m_canvas.AddSelectedShape(soloShape);
					}
					m_canvas.RemoveSelectedShape(compound);
					m_canvas.RemoveShape(compound);
					delete compound;
				}
			};
			if (m_canvas.IsCtrlPressed() && event.key.code == sf::Keyboard::S)
			{
				m_canvas.SetSaveStrategy(std::make_unique<SaveBinaryStrategy>());
				m_canvas.SaveIntoFile();
			};
			if (m_canvas.IsCtrlPressed() && event.key.code == sf::Keyboard::B)
			{
				m_canvas.SetSaveStrategy(std::make_unique<SaveTxtStrategy>());
				m_canvas.SaveIntoFile();
			};
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::LShift)
			{
				m_canvas.SetIsLShiftPressed(false);
			};
			if (event.key.code == sf::Keyboard::LControl)
			{
				m_canvas.SetIsCtrlPressed(false);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_canvas.SetIsMouseClicked(true);
				int id = 0;
				auto shapes = m_canvas.GetShapes();

				for (auto it = shapes.begin(); it != shapes.end(); it++)
				{
					if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						if (m_canvas.IsLShiftPressed())
						{
							if ((*it)->IsSelected())
							{
								(*it)->Unselect();
								m_canvas.RemoveSelectedShape(*it);
							}
							else
							{
								(*it)->Select();
								m_canvas.AddSelectedShape(*it);
							}
						}
						else
						{
							auto selectedShapes = m_canvas.GetSelectedShapes();
							for (auto it = selectedShapes.begin(); it != selectedShapes.end(); it++)
							{
								(*it)->Unselect();
							}
							(*it)->Select();
							m_canvas.ClearAllSelectedShapes();
							m_canvas.AddSelectedShape(*it);
						}
						m_canvas.SetDraggingShapeIdx(id);
						m_canvas.SetIsDragginShape(true);
						m_canvas.SetMouseShapeOffset(sf::Vector2f(event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x, event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y));
					}
					id++;
				}
			};
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_canvas.SetIsMouseClicked(false);
				m_canvas.SetIsDragginShape(false);
			};
			break;
		case sf::Event::MouseMoved:
			m_canvas.SetMouseX(event.mouseMove.x);
			m_canvas.SetMouseY(event.mouseMove.y);
			break;
		default:
			break;
		}
	};

private:
	ICanvas& m_canvas;
};
