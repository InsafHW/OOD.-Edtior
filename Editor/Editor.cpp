#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include <vector>
#include "OutlineDecorator.h"
#include "CompoundShape.h"
#include <iostream>

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



int main()
{
	//Creating the window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML Game");

	std::vector<IShape*> my_shapes;
	std::vector<IShape*> selected_shapes;

	OutlineDecorator* my_circle1 = new OutlineDecorator(new Circle(40, 40, 100));
	OutlineDecorator* my_circle2 = new OutlineDecorator(new Circle(80, 110, 100));
	OutlineDecorator* my_rectangle1 = new OutlineDecorator(new Rectangle(10, 34, 190, 344));
	OutlineDecorator* my_rectangle2 = new OutlineDecorator(new Rectangle(90, 43, 132, 844));

	my_shapes.push_back(my_circle1);
	my_shapes.push_back(my_circle2);
	my_shapes.push_back(my_rectangle1);
	my_shapes.push_back(my_rectangle2);

	window->setKeyRepeatEnabled(false);

	sf::Event event;

	//States for button/events
	bool mouseClicked = false;
	bool dragging = false;
	bool lShiftPressed = false;
	bool ctrlPressed = false;
	bool hasCompound = false;

	sf::Vector2f mouseShapeOffset;

	//Variables
	int mouseX = 0;
	int mouseY = 0;

	int dragginItemIdx = 0;

	CompoundShape compound;
	for (int i = 0; i < my_shapes.size(); i++)
	{
		compound.Add(my_shapes[i]);
	};

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

				for (int i = 0; i < my_shapes.size(); i++)
				{
					if (my_shapes[i]->GetGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						if (lShiftPressed)
						{
							if (my_shapes[i]->IsSelected())
							{
								my_shapes[i]->UnSelect();
							}
							else
							{
								my_shapes[i]->Select();
							}
						}
						dragging = true;
						dragginItemIdx = i;
						mouseShapeOffset.x = event.mouseButton.x - my_shapes[i]->GetGlobalBounds().left - my_shapes[i]->GetOrigin().x;
						mouseShapeOffset.y = event.mouseButton.y - my_shapes[i]->GetGlobalBounds().top - my_shapes[i]->GetOrigin().y;
					}

				};
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
			{
				for (int i = 0; i < my_shapes.size(); i++)
				{
					if (my_shapes[i]->IsSelected())
					{
						compound.Remove(my_shapes[i]);
					}
				}
				hasCompound = false;
			}

			if (ctrlPressed && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				std::cout << "GROUPPING..." << std::endl;
				for (int i = 0; i < my_shapes.size(); i++)
				{
					if (my_shapes[i]->IsSelected())
					{
						compound.Add(my_shapes[i]);
					}
				}
				hasCompound = true;
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				mouseClicked = false;
				dragging = false;
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

		//LOGIC

		if (dragging == true && my_shapes[dragginItemIdx]->IsSelected())
		{
			if (hasCompound)
			{
				compound.Move(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);
			}
			else
			{
				my_shapes[dragginItemIdx]->SetPosition(mouseX - mouseShapeOffset.x, mouseY - mouseShapeOffset.y);

			}
		}

		//RENDERING
		window->clear();

		for (int i = 0; i < my_shapes.size(); i++)
		{
			my_shapes[i]->Draw(window);
		}

		window->display();
	}

	//Close the program
	return 0;
}