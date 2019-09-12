#pragma once

class FileSystem
{
public:
	static const std::string FileSystem::GetFileNameFromPath(const std::string& path);
	static const std::string FileSystem::GetIntactFileNameFromPath(const std::string& path);

};