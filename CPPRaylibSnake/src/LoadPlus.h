#pragma once
#include "Raylib/raylib.h"
#include <string>

static class LoadPlus
{

public:
	static Texture2D LoadTexturePlus(const char* filePathFromResources)
	{
		std::string filePath;

		std::string workingDirectory = GetWorkingDirectory();
		if (workingDirectory.find("Debug.DLL") != std::string::npos)
		{
			filePath = "../../../../resources/" + std::string(filePathFromResources);
		}
		else
		{
			filePath = "../resources/" + std::string(filePathFromResources);
		}

		Image image = LoadImage(filePath.c_str());
		Texture2D tex = LoadTextureFromImage(image);
		UnloadImage(image);
		
		return tex;
	}
};
