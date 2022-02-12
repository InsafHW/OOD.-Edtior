#include "SaveBinaryStrategy.h"

void SaveBinaryStrategy::SaveFile(std::list<CompoundShape*> shapes)
{
	std::cout << "Binary Saving" << std::endl;
	std::ifstream inp("data.bin", std::ios_base::out | std::ios_base::binary);
	inp.close();

	std::ofstream out;
	out.open("data.bin", std::ios::binary);
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