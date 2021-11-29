#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "CanvasState.h"
#include "CompoundShape.h"
#include "DragAndDropState.h"
#include "StateType.h"
#include "OutlineDecorator.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include <fstream>
#include "ReadBinary.h"

struct SaveDataBinary
{
	float topLeftX;
	float topLeftY;
	float width;
	float height;
	sf::Color fillColor;
	sf::Color outlineColor;
	IShapeType type;
};

class Canvas
{
public:
	Canvas(std::list<CompoundShape*> shapes)
		: m_shapes(shapes),
		m_type(StateType::DRAG_AND_DROP)
	{
		ReadBinaryFn();
		auto binShapes = binaryReader.GetShapes("data.bin");
		std::cout << "BinShapes = " << binShapes.size() << std::endl;
		//SetDragAndDropStateMan();
	}

	void PollEvents(sf::Event event, sf::RenderWindow* window)
	{
		//std::cout << m_shapes.size() << std::endl;
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

	void SaveBinary()
	{
		std::ifstream inp("data.bin", std::ios_base::in | std::ios_base::out);
		inp.close();

		std::ofstream out;
		out.open("data.bin", std::ios::binary);
		std::cout << m_shapes.size() << std::endl << std::endl;
		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			auto x = (*it)->GetShapes();
			std::cout << "1";
			for (auto innerIt = x.begin(); innerIt != x.end(); innerIt++)
			{
				auto bounds = (*innerIt)->GetGlobalBounds();
				SaveDataBinary data;
				data.topLeftX = bounds.left;
				data.topLeftY = bounds.top;
				data.height = bounds.height;
				data.width = bounds.width;
				data.type = (*innerIt)->GetType();

				out.write((const char*)&data, sizeof(data));
			}
		}
		std::cout << std::endl;

		out.close();
	};

	void ReadBinaryFn()
	{
		std::ifstream in;
		in.open("data.bin", std::ios::binary);

		SaveDataBinary data;

		in.seekg(0, std::ios::end);
		int size = in.tellg();

		in.close();
		in.open("data.bin", std::ios::binary);

		std::cout << size << std::endl;

		for (int i = 0; i < size; i += sizeof(data))
		{
			CompoundShape* shape = new CompoundShape();
			in.read((char*)&data, sizeof(data));
			if (data.type == IShapeType::CIRCLE)
			{
				std::cout << "Circle" << std::endl;
				shape->Add(new OutlineDecorator(new Circle(data.width / 2 + data.topLeftX, data.height / 2 + data.topLeftY, data.height / 2)));
			}
			else if (data.type == IShapeType::RECTANGLE)
			{
				std::cout << "RECTANGLE" << std::endl;
				shape->Add(new OutlineDecorator(new Rectangle(data.topLeftX, data.topLeftY, data.height + data.topLeftX, data.height + data.topLeftY)));

			}
			else
			{
				std::cout << "Triangle" << std::endl;

			}
			m_shapes.push_back(shape);
		}


		/*while (!in.eof() && size > 0)
		{
			std::cout << "!" << std::endl;
			std::cout << "Reading" << in.eof();
			CompoundShape* shape = new CompoundShape();

			in.read((char*)&data, sizeof(data));


			std::cout << "height = " << data.height << "; topLeftX = " << data.topLeftX << "; topLeftY = " << data.topLeftY << ";width = " << data.width << std::endl;

			if (data.type == IShapeType::CIRCLE)
			{
				std::cout << "Circle" << std::endl;
				shape->Add(new OutlineDecorator(new Circle(data.width / 2 + data.topLeftX, data.height / 2 + data.topLeftY, data.height / 2)));
			}
			else if (data.type == IShapeType::RECTANGLE)
			{
				std::cout << "RECTANGLE" << std::endl;
				shape->Add(new OutlineDecorator(new Rectangle(data.topLeftX, data.topLeftY, data.height + data.topLeftX, data.height + data.topLeftY)));

			}
			else
			{
				std::cout << "Triangle" << std::endl;

			}
			m_shapes.push_back(shape);
		}*/

		in.close();
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

	ReadBinary binaryReader;

	void DragAndDropPollEvent(sf::Event event, sf::RenderWindow* window);
	void AddRectanglePollEvent(sf::Event event, sf::RenderWindow* window);
	void AddTrianglePollEvent(sf::Event event, sf::RenderWindow* window);
	void AddCirclePollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeFillColorPollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeOutlineColorPollEvent(sf::Event event, sf::RenderWindow* window);
	void ChangeOutlineThicknessPollEvent(sf::Event event, sf::RenderWindow* window);
};