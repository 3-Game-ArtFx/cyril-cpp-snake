#pragma once
#include <math.h>
#include "Raylib/raylib.h"
#include "Int2.h"

static class TextPlus
{
public:
	static void DrawTextCenter(const char* text, Int2 pos, int fontSize, Color color)
	{
		DrawTextCenter(text, pos.x, pos.y, fontSize, color);
	}

	static void DrawTextCenter(const char* text, int posX, int posY, int fontSize, Color color)
	{
		int textSizeX = MeasureText(text, fontSize);
		int textSizeY = fontSize;

		int reelTextPosX = posX - ceil(textSizeX / 2);
		int reelTextPosY = posY - ceil(textSizeY / 2);

		DrawText(text, reelTextPosX, reelTextPosY, fontSize, color);
	}
};
