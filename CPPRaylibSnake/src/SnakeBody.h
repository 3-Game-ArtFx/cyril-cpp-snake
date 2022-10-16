#pragma once
#include "Raylib/raylib.h"
#include "Int2.h"
#include "Grid.h"

class SnakeBody
{
private:
	Grid* grid;
	Int2 gridPos;

	Texture2D bodyTex;

public:
	SnakeBody(Grid* grid, Int2 gridPos);
	~SnakeBody();

	void Draw();
	void Remove();
	void SetTex(Texture2D tex);
};

