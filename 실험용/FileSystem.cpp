#include "pch.h"
#include "FileSystem.h"

const std::string FileSystem::GetFileNameFromPath(const std::string& path)
{
	uint lastIndex = static_cast<uint>(path.find_last_of("\\/"));
	std::string fileName = path.substr(lastIndex + 1, path.length());

	return fileName;
}

const std::string FileSystem::GetIntactFileNameFromPath(const std::string& path)
{
	std::string fileName = GetFileNameFromPath(path);
	uint lastIndex = static_cast<uint>(fileName.find_last_of("."));

	return fileName.substr(0, lastIndex);
}
