#include "SnakeHead.h"
#include "TextPlus.h"
#include "LoadPlus.h"

SnakeHead::SnakeHead(Direction baseDirection, Grid* grid, Int2 baseGridPos, int numberOfBaseBodyParts)
{
	this->grid = grid;
	gameState = GameState::NotStarted;

	Initialize(baseGridPos, baseDirection, numberOfBaseBodyParts);
}

SnakeHead::~SnakeHead()
{
	if (texLoaded)
	{
		UnloadTexture(headLeftTex);
		UnloadTexture(headUpTex);
		UnloadTexture(headRightTex);
		UnloadTexture(headDownTex);
	}
}

void SnakeHead::Update()
{
	Move();
}


void SnakeHead::ChangeDirection(Direction newDirection)
{
	switch (direction)
	{
		case Direction::Left:
			if (newDirection != Direction::Right)
			{
				direction = newDirection;
			}
			break;
		case Direction::Up:
			if (newDirection != Direction::Down)
			{
				direction = newDirection;
			}
			break;
		case Direction::Right:
			if (newDirection != Direction::Left)
			{
				direction = newDirection;
			}
			break;
		case Direction::Down:
			if (newDirection != Direction::Up)
			{
				direction = newDirection;
			}
			break;
		default:
			direction = newDirection;
			return;
	}

	
}

void SnakeHead::Move()
{
	Int2 newGridPos = gridPos;
	bool hasEatApple = false;

	switch (direction)
	{
		case Direction::Left:
			newGridPos.x--;
			break;

		case Direction::Up:
			newGridPos.y--;
			break;

		case Direction::Right:
			newGridPos.x++;
			break;

		case Direction::Down:
			newGridPos.y++;
			break;

		default:
			return;
	}

	if (grid->IsObstacle(newGridPos))
	{
		Defeat();
	}
	else
	{
		hasEatApple = grid->IsApple(newGridPos);

		grid->SetObstacles(gridPos, false);
		MoveBody(gridPos, hasEatApple);

		gridPos = newGridPos;
		grid->SetObstacles(gridPos, true);

		if (hasEatApple)
		{
			if (!grid->PlaceNewApple())
			{
				Victory();
			}
		}
	}
}

void SnakeHead::MoveBody(Int2 newBodyPartGridPos, bool hasEatApple)
{
	int bodyPenultimatePart = body.size() - 1;
	SnakeBody* lastBody = &body[bodyPenultimatePart];

	if (hasEatApple)
	{
		body.push_back(*lastBody);
	}
	else
	{
		lastBody->Remove();
	}

	for (int i = bodyPenultimatePart; i > 0; i--)
	{
		body[i] = body[i - 1];
	}

	body[0] = SnakeBody(grid, newBodyPartGridPos);
	body[0].SetTex(bodyTex);
}

void SnakeHead::Initialize(Int2 baseGridPos, Direction baseDirection, int numberOfBaseBodyParts)
{
	grid->ResetGrid();

	direction = baseDirection;
	gridPos = baseGridPos;

	this->grid->SetObstacles(baseGridPos, true);

	for (int i = 0; i < body.size(); i++)
	{
		body[i].Remove();
	}
	body.clear();

	if (numberOfBaseBodyParts > 0)
	{
		Int2 bodyPartGridPosOffset;
		switch (baseDirection)
		{
		case Direction::Left:
			bodyPartGridPosOffset = Int2(1, 0);
			break;
		case Direction::Up:
			bodyPartGridPosOffset = Int2(0, 1);
			break;
		case Direction::Right:
			bodyPartGridPosOffset = Int2(-1, 0);
			break;
		case Direction::Down:
			bodyPartGridPosOffset = Int2(0, -1);
			break;
		default:
			return;
		}

		for (int i = 1; i <= numberOfBaseBodyParts; i++)
		{
			Int2 bodyPartGridPos = gridPos + (bodyPartGridPosOffset * i);
			if (grid->IsPosInsideGrid(bodyPartGridPos))
			{
				body.push_back(SnakeBody(grid, bodyPartGridPos));
			}
		}
	}

	grid->PlaceNewApple();
}

void SnakeHead::StartNewGame(Int2 baseGridPos, Direction baseDirection, int numberOfBaseBodyParts, bool regenerateGame)
{
	if (regenerateGame)
	{
		Initialize(baseGridPos, baseDirection, numberOfBaseBodyParts);
	}
	gameState = GameState::Play;
}

void SnakeHead::Defeat()
{
	gameState = GameState::Defeat;
}

void SnakeHead::Victory()
{
	gameState = GameState::Victory;
}

void SnakeHead::Draw(int screenWidth)
{
	Int2 realPos = grid->GridToRealPos(gridPos);
	//Int2 cellSize = grid->GetCellSize();

	//DrawRectangle(realPos.x, realPos.y, cellSize.x, cellSize.y, GRAY);

	Texture2D choosenTex;
	switch (direction)
	{
	case Direction::Left:
		choosenTex = headLeftTex;
		break;
	case Direction::Up:
		choosenTex = headUpTex;
		break;
	case Direction::Right:
		choosenTex = headRightTex;
		break;
	case Direction::Down:
		choosenTex = headDownTex;
		break;
	}
	DrawTexture(choosenTex, realPos.x, realPos.y, WHITE);

	for (int i = 0; i < body.size(); i++)
	{
		body[i].Draw();
	}

	const char* bodyLength = TextFormat("Score : %i", body.size());
	TextPlus::DrawTextCenter(bodyLength, 2 * floor(screenWidth / 3), 40, 25, WHITE);
}

void SnakeHead::LoadTex()
{
	headLeftTex = LoadPlus::LoadTexturePlus("SnakeHeadLeft.png");
	headUpTex = LoadPlus::LoadTexturePlus("SnakeHeadUp.png");
	headRightTex = LoadPlus::LoadTexturePlus("SnakeHeadRight.png");
	headDownTex = LoadPlus::LoadTexturePlus("SnakeHeadDown.png");
	bodyTex = LoadPlus::LoadTexturePlus("SnakeBody.png");

	texLoaded = true;

	for (int i = 0; i < body.size(); i++)
	{
		body[i].SetTex(bodyTex);
	}
}
