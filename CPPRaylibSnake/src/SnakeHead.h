#pragma once
#include <vector>
#include "Raylib/raylib.h"
#include "Int2.h"
#include "Direction.h"
#include "Grid.h"
#include "SnakeBody.h"
#include "GameState.h"

class SnakeHead
{
private:
	Direction direction;
	Grid* grid;
	Int2 gridPos;
	std::vector<SnakeBody> body;

	bool texLoaded = false;
	Texture2D headLeftTex;
	Texture2D headUpTex;
	Texture2D headRightTex;
	Texture2D headDownTex;
	Texture2D bodyTex;

	void Move();
	void MoveBody(Int2 newBodyPartGridPos, bool hasEatApple);

	void Initialize(Int2 baseGridPos, Direction baseDirection, int numberOfBaseBodyParts);
	void Defeat();
	void Victory();

public:
	SnakeHead(Direction baseDirection, Grid* grid, Int2 baseGridPos, int numberOfBaseBodyParts);
	~SnakeHead();

	void Update();
	void Draw(int screenWidth);

	void LoadTex();

	void StartNewGame(Int2 baseGridPos, Direction baseDirection, int numberOfBaseBodyParts, bool regenerateGame);
	void ChangeDirection(Direction newDirection);

	GameState gameState;
};

