#include "SnakeBody.h"

SnakeBody::SnakeBody(Grid* grid, Int2 gridPos)
{
	this->grid = grid;
	this->gridPos = gridPos;

	grid->SetObstacles(gridPos, true);
}

SnakeBody::~SnakeBody()
{
}

void SnakeBody::Remove()
{
	grid->SetObstacles(gridPos, false);
}

void SnakeBody::Draw()
{
	Int2 realPos = grid->GridToRealPos(gridPos);
	//Int2 cellSize = grid->GetCellSize();

	//DrawRectangle(realPos.x, realPos.y, cellSize.x, cellSize.y, DARKGRAY);
	DrawTexture(bodyTex, realPos.x, realPos.y, WHITE);
}

void SnakeBody::SetTex(Texture2D tex)
{
	bodyTex = tex;
}
