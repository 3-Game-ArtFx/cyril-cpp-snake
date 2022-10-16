#include "Grid.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "LoadPlus.h"

Grid::Grid(Int2 gridRealSize, Int2 cellSize, Int2 offset)
{
	Int2 gridSize;

	gridSize.x = floor(gridRealSize.x / cellSize.x);
	gridSize.y = floor(gridRealSize.y / cellSize.y);
	
	obstaclesOnGrid.Resize(false, gridSize);

	this->cellSize = cellSize;
	this->gridSize = gridSize;
	this->gridOffset = offset;
}

Grid::~Grid()
{
	obstaclesOnGrid.~Array2D();
	if (texLoaded)
	{
		UnloadTexture(appleTex);
	}
}

Int2 Grid::GridToRealPos(Int2 gridPos)
{
	Int2 realPos;
	realPos.x = gridPos.x * cellSize.x + gridOffset.x;
	realPos.y = gridPos.y * cellSize.y + gridOffset.y;
	return realPos;
}

Int2 Grid::GetCellSize()
{
	return cellSize;
}

void Grid::SetObstacles(Int2 gridPos, bool value)
{
	obstaclesOnGrid.SetValue(gridPos, value);
}

bool Grid::IsObstacle(Int2 gridPos)
{
	if (!IsPosInsideGrid(gridPos)) return true;
	return obstaclesOnGrid.GetValue(gridPos);
}

bool Grid::IsPosInsideGrid(Int2 gridPos)
{
	if (gridPos.x < 0 || gridPos.x >= gridSize.x || gridPos.y < 0 || gridPos.y >= gridSize.y) return false;
	return true;
}

bool Grid::IsApple(Int2 gridPos)
{
	return gridPos == appleGridPos;
}

bool Grid::PlaceNewApple()
{
	std::vector<Int2> freeCells;
	for (int i = 0; i < obstaclesOnGrid.GetSizeX(); i++)
	{
		for (int j = 0; j < obstaclesOnGrid.GetSizeY(i); j++)
		{
			Int2 pos = Int2(i, j);
			if (!obstaclesOnGrid.GetValue(pos))
			{
				freeCells.push_back(pos);
			}
		}
	}

	if (freeCells.size() > 0)
	{
		srand(time(NULL));
		int cellToPlaceApple = rand() % freeCells.size();
		appleGridPos = freeCells[cellToPlaceApple];
		return true;
	}
	return false;
}

void Grid::ResetGrid()
{
	for (int i = 0; i < obstaclesOnGrid.GetSizeX(); i++)
	{
		for (int j = 0; j < obstaclesOnGrid.GetSizeY(i); j++)
		{
			Int2 pos = Int2(i, j);
			obstaclesOnGrid.SetValue(pos, false);
		}
	}
}


void Grid::Draw()
{
	if (gridOffset.x != 0 && gridOffset.y != 0)
	{
		DrawRectangleLines(gridOffset.x - 1, gridOffset.y - 1, (gridSize.x * cellSize.x) + 2, (gridSize.y * cellSize.y) + 2, WHITE);
	}

	Int2 appleRealPos = GridToRealPos(appleGridPos);

	//DrawRectangle(appleRealPos.x, appleRealPos.y, cellSize.x, cellSize.y, RED);
	DrawTexture(appleTex, appleRealPos.x, appleRealPos.y, WHITE);
}

void Grid::LoadTex()
{
	appleTex = LoadPlus::LoadTexturePlus("Apple.png");
	texLoaded = true;
}