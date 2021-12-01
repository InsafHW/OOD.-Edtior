#pragma once
#include "SaveStrategy.h"
#include <fstream>
#include "IShape.h"

class SaveTxtStrategy : public SaveStrategy
{
public:
	void SaveFile(std::list<CompoundShape*> shapes) override
	{
		std::cout << "Txt Saving" << std::endl;

		std::ifstream inp("data.txt");
		inp.close();

		std::ofstream out;
		out.open("data.txt");
		for (auto it = shapes.begin(); it != shapes.end(); it++)
		{
			auto x = (*it)->GetShapes();
			for (auto innerIt = x.begin(); innerIt != x.end(); innerIt++)
			{
				auto bounds = (*innerIt)->GetGlobalBounds();
				SavedShapeData data;
				data.topLeftX = bounds.left;
				data.topLeftY = bounds.top;
				data.height = bounds.height;
				data.width = bounds.width;
				data.type = (*innerIt)->GetType();
				data.fillColor = (*innerIt)->GetFillColor();
				data.outlineColor = (*innerIt)->GetOutlineColor();

				out.write((const char*)&data, sizeof(data));
			}
		}

		out.close();
	};
};

