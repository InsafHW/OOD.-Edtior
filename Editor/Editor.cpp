#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include <vector>
#include "OutlineDecorator.h"
#include "CompoundShape.h"
#include <iostream>
#include "Singleton.h"

int main()
{
	//Creating the window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML Game");
	std::list<IShape*> list;
	std::list<CompoundShape*> compound;
	std::list<IShape*> selectedShapes;
	std::list<CompoundShape*> selectedCompounds;

	OutlineDecorator* my_circle1 = new OutlineDecorator(new Circle(40, 40, 100));
	OutlineDecorator* my_circle2 = new OutlineDecorator(new Circle(80, 110, 100));
	OutlineDecorator* my_rectangle1 = new OutlineDecorator(new Rectangle(10, 34, 190, 344));
	OutlineDecorator* my_rectangle2 = new OutlineDecorator(new Rectangle(90, 43, 132, 844));

	list.push_back(my_circle1);
	list.push_back(my_circle2);
	list.push_back(my_rectangle1);
	list.push_back(my_rectangle2);

	window->setKeyRepeatEnabled(false);


	sf::Event event;

	//States for button/events
	bool mouseClicked = false;
	bool draggingShape = false;
	bool draggingCompound = false;
	bool lShiftPressed = false;
	bool ctrlPressed = false;

	sf::Vector2f mouseShapeOffset;

	//Variables
	int mouseX = 0;
	int mouseY = 0;

	int draggingShapeIdx = 0;
	int draggingCompoundIdx = 0;

	double preX = 0;
	double preY = 0;

	//Game loop
	while (window->isOpen())
	{
		//EVENTS
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift)
			{
				lShiftPressed = true;
				std::cout << "Left Shift pressed" << std::endl;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
			{
				lShiftPressed = false;
				std::cout << "Left Shift released" << std::endl;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
			{
				ctrlPressed = true;
				std::cout << "Left control pressed" << std::endl;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
			{
				ctrlPressed = false;
				std::cout << "Left control released" << std::endl;
			}

			//LMB Pressed
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				mouseClicked = true;
				int id = 0;
				for (auto it = list.begin(); it != list.end(); it++)
				{
					if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						if (selectedShapes.size() == 0 && compound.size() == 0)
						{
							if ((*it)->IsSelected())
							{
								selectedShapes.remove(*it);
							}
							else
							{
								(*it)->Select();
								selectedShapes.push_back(*it);
							}
						}
						else if (lShiftPressed)
						{
							if ((*it)->IsSelected())
							{
								(*it)->UnSelect();
								selectedShapes.remove(*it);
							}
							else
							{
								(*it)->Select();
								selectedShapes.push_back(*it);
							}
						}
						draggingShapeIdx = id;
						draggingShape = true;
						preX = event.mouseButton.x;
						preY = event.mouseButton.y;
						mouseShapeOffset.x = event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
						mouseShapeOffset.y = event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
						break;
					}
					id++;
				}
				id = 0;
				draggingCompound = false;
				for (auto it = compound.begin(); it != compound.end(); it++)
				{
					if ((*it)->IsMouseInGroup(event.mouseButton.x, event.mouseButton.y))
					{
						draggingCompoundIdx = id;
						std::cout << "HERRRRR";
						draggingCompound = true;
						auto bounds = (*it)->GetGlobalBounds();
						auto origin = (*it)->GetOrigin();
						mouseShapeOffset.x = event.mouseButton.x - bounds.left - origin.x;
						mouseShapeOffset.y = event.mouseButton.y - bounds.top - origin.y;
						break;
					}
					id++;
				}
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && selectedShapes.size() > 1)
			{
				std::cout << "GROUPPING..." << std::endl;
				CompoundShape* comp = new CompoundShape();
				for (auto it = selectedShapes.begin(); it != selectedShapes.end(); it++)
				{
					list.remove(*it);
					comp->Add(*it);
					(*it)->SetIsPartOfCompound();
				}
				compound.push_back(comp);
				selectedShapes.clear();
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U && compound.size() > 0)
			{
				std::cout << "UNGROUPPING..." << std::endl;
				auto shapes = (*std::next(compound.begin(), draggingCompoundIdx))->GetShapes();
				for (auto it = shapes.begin(); it != shapes.end(); it++)
				{
					list.push_back(*it);
					selectedShapes.push_back(*it);
					(*it)->UnsetIsPartOfCompound();
				}
				compound.remove(*std::next(compound.begin(), draggingCompoundIdx));
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				mouseClicked = false;
				draggingShape = false;
				draggingCompound = false;
			}

			//Mouse Moved in window
			if (event.type == sf::Event::MouseMoved)
			{
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
			}

			//Event type is window closed
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}


		// LOGIC
		if (draggingShape == true)
		{
			std::cout << "Dragging Shape" << std::endl;
			auto candidate = (*std::next(list.begin(), draggingShapeIdx));
			if (candidate->IsSelected())
			{
				candidate->SetPosition(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);
			}
		}
		if (draggingCompound == true && event.type == sf::Event::MouseMoved)
		{
			std::cout << "Dragging Compound" << std::endl;
			(*std::next(compound.begin(), draggingCompoundIdx))->Move(mouseX, mouseY);
		}

		//RENDERING
		window->clear();

		for (auto it = list.begin(); it != list.end(); it++)
		{
			(*it)->Draw(window);
		}
		for (auto it = compound.begin(); it != compound.end(); it++)
		{
			(*it)->Draw(window);
		}

		window->display();
	}

	//Close the program
	return 0;
}

int main()
{
	auto& instance = Singleton::GetInstance();
};