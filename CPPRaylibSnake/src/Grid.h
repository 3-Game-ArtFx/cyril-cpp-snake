#pragma once
#include "Raylib/raylib.h"
#include "Int2.h"
#include "Array2D.h"

class Grid
{
private:
	Array2D<bool> obstaclesOnGrid = Array2D<bool>(false); 
	Int2 cellSize;
	Int2 gridSize;
	Int2 gridOffset;

	Int2 appleGridPos;

	bool texLoaded = false;
	Texture2D appleTex;

public:
	Grid(Int2 gridRealSize, Int2 cellSize, Int2 offset);
	~Grid();

	Int2 GridToRealPos(Int2 gridPos);
	Int2 GetCellSize();

	void Draw();

	void LoadTex();

	void ResetGrid();
	void SetObstacles(Int2 gridPos, bool value);
	bool IsObstacle(Int2 gridPos);
	bool IsPosInsideGrid(Int2 gridPos);
	bool IsApple(Int2 gridPos);
	bool PlaceNewApple();
};

