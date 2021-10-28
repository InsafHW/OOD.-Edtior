#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include <vector>
#include "OutlineDecorator.h"
#include "CompoundShape.h"
#include <iostream>
#include "Singleton.h"

//Singleton* editor = Singleton::getInstance();

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(400, 800), "Start Editor");
//	sf::CircleShape circle(100.f);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(circle);
//		window.display();
//	}
//}

//int main() {
//	sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML Game");
//	srand((unsigned)time(nullptr));
//
//	sf::Event event;
//
//	bool mouseClicked = false;
//	bool mouseInsideRect = false;
//	bool dragging = false;
//
//	sf::Vector2f mouseRectOffset;
//
//	int mouseX = 0;
//	int mouseY = 0;
//
//	std::vector<Shape> shapeVec;
//	Shape* currentShape = nullptr;          // keep track of current shape being moved
//
//	for (int i = 0; i < 10; ++i) {
//		auto shape = new Shape({ 64.f,64.f });
//		shape->shape.setPosition(rand() % 1100 + 100, rand() % 650 + 100);
//		shapeVec.push_back(*shape);
//
//	}
//	while (window.isOpen()) {
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//				window.close();
//			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
//				auto shape = new Shape({ 64.f,64.f });
//				shape->shape.setPosition(rand() % 1100 + 100, rand() % 650 + 100);
//				shapeVec.push_back(*shape);
//			}
//
//
//		}
//
//		// get the mouse position
//		auto mpos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//
//		// Moving the shapes
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//			if (mpos.x >= 0 && mpos.x < window.getSize().x && mpos.y >= 0 * mpos.y < window.getSize().y && !dragging) {
//				dragging = true;
//				for (auto& it : shapeVec) {
//					if (it.shape.getGlobalBounds().contains(mpos.x, mpos.y)) {
//						it.selected = true;
//						currentShape = &it;
//						break;
//					}
//				}
//			}
//		}
//		else {
//
//			dragging = false;
//			if (currentShape)
//				currentShape->selected = false;
//		}
//
//		// removing the shapes
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
//			if (mpos.x >= 0 && mpos.x < window.getSize().x && mpos.y >= 0 * mpos.y < window.getSize().y) {
//				auto shapeIt = shapeVec.begin();
//				while (shapeIt != shapeVec.end()) {
//					auto it = *shapeIt;
//					if (it.shape.getGlobalBounds().contains(mpos.x, mpos.y)) {
//						shapeIt = shapeVec.erase(shapeIt);
//					}
//					else {
//						++shapeIt;
//					}
//				}
//			}
//		}
//
//		if (dragging == true) {
//			for (int i = 0; i < shapeVec.size(); i++) {
//				if (shapeVec[i].selected)
//					shapeVec[i].shape.setPosition(mpos.x, mpos.y);
//
//			}
//		}
//
//		window.clear();
//
//		for (int i = 0; i < shapeVec.size(); i++) {
//			window.draw(shapeVec[i].shape);
//		}
//
//		window.display();
//	}
//}



//int main()
//{
//	//Creating the window
//	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML Game");
//
//	std::list<IShape*> my_shapes;
//	std::list<CompoundShape*> compound_shapes;
//
//	OutlineDecorator* my_circle1 = new OutlineDecorator(new Circle(40, 40, 100));
//	OutlineDecorator* my_circle2 = new OutlineDecorator(new Circle(80, 110, 100));
//	OutlineDecorator* my_rectangle1 = new OutlineDecorator(new Rectangle(10, 34, 190, 344));
//	OutlineDecorator* my_rectangle2 = new OutlineDecorator(new Rectangle(90, 43, 132, 844));
//
//	my_shapes.push_back(my_circle1);
//	my_shapes.push_back(my_circle2);
//	my_shapes.push_back(my_rectangle1);
//	my_shapes.push_back(my_rectangle2);
//
//	window->setKeyRepeatEnabled(false);
//
//	sf::Event event;
//
//	//States for button/events
//	bool mouseClicked = false;
//	bool dragging = false;
//	bool lShiftPressed = false;
//	bool ctrlPressed = false;
//	bool hasCompound = false;
//
//	sf::Vector2f mouseShapeOffset;
//
//	//Variables
//	int mouseX = 0;
//	int mouseY = 0;
//
//	int dragginItemIdx = -1;
//	int dragginCompoundIdx = -1;
//	int selectedItemsCount = 0;
//
//	/*for (int i = 0; i < my_shapes.size(); i++)
//	{
//		compound.Add(my_shapes[i]);
//	};*/
//
//	//Game loop
//	while (window->isOpen())
//	{
//		//EVENTS
//		while (window->pollEvent(event))
//		{
//			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift)
//			{
//				lShiftPressed = true;
//				std::cout << "Left Shift pressed" << std::endl;
//			}
//
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
//			{
//				lShiftPressed = false;
//				std::cout << "Left Shift released" << std::endl;
//			}
//
//			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
//			{
//				ctrlPressed = true;
//				std::cout << "Left control pressed" << std::endl;
//			}
//
//			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
//			{
//				ctrlPressed = false;
//				std::cout << "Left control released" << std::endl;
//			}
//
//			//LMB Pressed
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				mouseClicked = true;
//
//				int id = 0;
//				int compId = 0;
//				for (auto it = compound_shapes.begin(); it != compound_shapes.end(); it++)
//				{
//					compId++;
//					if ((*it)->IsMouseInGroup(event.mouseButton.x, event.mouseButton.y))
//					{
//						dragginCompoundIdx = compId;
//					}
//				}
//				for (auto it = my_shapes.begin(); it != my_shapes.end(); it++)
//				{
//					if ((*it)->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						std::cout << "Inside shape" << std::endl;
//						if (selectedItemsCount == 0)
//						{
//							(*it)->Select();
//						}
//						else if (lShiftPressed)
//						{
//							if ((*it)->IsSelected())
//							{
//								(*it)->UnSelect();
//							}
//							else
//							{
//								(*it)->Select();
//							}
//						}
//						dragging = true;
//						dragginItemIdx = id++;
//						std::cout << "dragginItemIdx = " << id << std::endl;
//						mouseShapeOffset.x = event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
//						mouseShapeOffset.y = event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
//					}
//
//				};
//			}
//
//			/*if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
//			{
//				for (auto it = compound_shapes.begin(); it != compound_shapes.end(); it++)
//				{
//					auto shapes = (*it)->GetShapes();
//					for (auto itInner = shapes.begin(); itInner != shapes.end(); itInner++)
//					{
//						shapes.push_back(*itInner);
//					}
//					(*it)->RemoveAll();
//				}
//			}*/
//
//			/*if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
//			{
//				std::cout << "GROUPPING..." << std::endl;
//				CompoundShape* compound = new CompoundShape();
//				for (auto it = my_shapes.begin(); it != my_shapes.end(); it++)
//				{
//					if ((*it)->IsSelected())
//					{
//						compound->Add((*it));
//						my_shapes.remove(*it);
//					}
//				}
//			}*/
//
//			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
//			{
//				mouseClicked = false;
//				dragging = false;
//			}
//
//			//Mouse Moved in window
//			if (event.type == sf::Event::MouseMoved)
//			{
//				mouseX = event.mouseMove.x;
//				mouseY = event.mouseMove.y;
//			}
//
//			//Event type is window closed
//			if (event.type == sf::Event::Closed)
//			{
//				window->close();
//			}
//		}
//
//		//LOGIC
//
//		if (dragging == true)
//		{
//			if (dragginItemIdx != -1)
//			{
//				(*std::next(my_shapes.begin(), dragginItemIdx))->SetPosition(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);
//
//			}
//		}
//
//		//RENDERING
//		window->clear();
//
//		for (auto it = my_shapes.begin(); it != my_shapes.end(); it++)
//		{
//			(*it)->Draw(window);
//		}
//
//		window->display();
//	}
//
//	//Close the program
//	return 0;
//}

//int main()
//{
//	std::vector<IShape*> my_shapes;
//
//
//	OutlineDecorator* my_circle1 = new OutlineDecorator(new Circle(40, 40, 100));
//	OutlineDecorator* my_circle2 = new OutlineDecorator(new Circle(80, 110, 100));
//	OutlineDecorator* my_rectangle1 = new OutlineDecorator(new Rectangle(10, 34, 190, 344));
//	OutlineDecorator* my_rectangle2 = new OutlineDecorator(new Rectangle(90, 43, 132, 844));
//
//	my_shapes.push_back(my_circle1);
//	my_shapes.push_back(my_circle2);
//	my_shapes.push_back(my_rectangle1);
//	my_shapes.push_back(my_rectangle2);
//
//	auto& game = Singleton::getInstance();
//	game.AddShape(my_circle1);
//	game.AddShape(my_circle2);
//	game.AddShape(my_rectangle1);
//	game.AddShape(my_rectangle2);
//	game.Start();
//};




int main()
{
	//Creating the window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML Game");
	std::list<IShape*> list;
	std::list<CompoundShape*> compound;
	std::list<IShape*> selected;

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
	bool dragging = false;
	bool compoundDragging = false;
	bool lShiftPressed = false;
	bool ctrlPressed = false;
	bool hasCompound = false;

	sf::Vector2f mouseShapeOffset;

	//Variables
	int mouseX = 0;
	int mouseY = 0;

	int dragginItemIdx = 0;
	int selectedItemsCount = 0;
	int compoundDraggingIdx = 0;

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
						if (selectedItemsCount == 0 && compound.size() == 0)
						{
							if ((*it)->IsSelected())
							{
								selectedItemsCount--;
							}
							else
							{
								(*it)->Select();
								selectedItemsCount++;
								selected.push_back(*it);
							}
						}
						else if (lShiftPressed)
						{
							if ((*it)->IsSelected())
							{
								(*it)->UnSelect();
								selectedItemsCount--;
								selected.remove(*it);
							}
							else
							{
								(*it)->Select();
								selectedItemsCount++;
								selected.push_back(*it);
							}
						}
						dragginItemIdx = id;
						dragging = true;
						mouseShapeOffset.x = event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
						mouseShapeOffset.y = event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
					}
					id++;
				}
				id = 0;
				compoundDragging = false;
				for (auto it = compound.begin(); it != compound.end(); it++)
				{
					if ((*it)->IsMouseInGroup(event.mouseButton.x, event.mouseButton.y))
					{
						compoundDraggingIdx = id;
						std::cout << "HERRRRR";
						compoundDragging = true;
						mouseShapeOffset.x = event.mouseButton.x - (*it)->GetGlobalBounds().left - (*it)->GetOrigin().x;
						mouseShapeOffset.y = event.mouseButton.y - (*it)->GetGlobalBounds().top - (*it)->GetOrigin().y;
						break;
					}
					id++;
				}
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				std::cout << "GROUPPING..." << std::endl;
				CompoundShape* comp = new CompoundShape();
				for (auto it = selected.begin(); it != selected.end(); it++)
				{
					list.remove(*it);
					comp->Add(*it);
				}
				compound.push_back(comp);
				selected.clear();
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
			{
				std::cout << "UNGROUPPING..." << std::endl;
				auto shapes = (*std::next(compound.begin(), compoundDraggingIdx))->GetShapes();
				for (auto it = shapes.begin(); it != shapes.end(); it++)
				{
					(*it)->UnSelect();
					list.push_back(*it);
				}
				compound.remove(*std::next(compound.begin(), compoundDraggingIdx));
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				mouseClicked = false;
				dragging = false;
				compoundDragging = false;
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
		if (dragging == true)
		{
			std::cout << "x = " << mouseX << " ; y = " << mouseY << std::endl;
			if ((*std::next(list.begin(), dragginItemIdx))->IsSelected())
			{
				(*std::next(list.begin(), dragginItemIdx))->SetPosition(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);
			}
		}
		if (compoundDragging == true)
		{
			(*std::next(compound.begin(), compoundDraggingIdx))->Move(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);
			std::cout << "ZDEC";
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