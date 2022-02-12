#include "FileShapeReader.h"

std::list<CompoundShape*> FilesShapeReader::GetShapes() const
{
	this->StartReading();
	PrintReadingFileTypeHook();
	EndlineHook();
	return ReadShapes();
}

void FilesShapeReader::StartReading() const
{
	std::cout << "Reading... ";
}

void FilesShapeReader::EndlineHook() const
{
	std::cout << std::endl;
};