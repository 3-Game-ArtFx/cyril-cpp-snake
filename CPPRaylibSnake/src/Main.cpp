#include <math.h>
#include "Raylib/raylib.h"
#include "Int2.h"
#include "TextPlus.h"
#include "Grid.h"
#include "SnakeHead.h"
#include "GameState.h"

const int screenWidth = 820;
const int screenHeight = 550;

const int updateFrame = 7;
int frameCounter = 0;
Direction bufferDirection = Direction::Up;

void Update();
void Draw();

const Direction snakeBaseDirection = Direction::Up;
const Int2 snakeBaseGridPos = Int2(16, 9);
const int snakeBaseBodyLength = 3;

Grid gameGrid = Grid(Int2(800, 450), Int2(25, 25), Int2(10, 90));
SnakeHead snake = SnakeHead(snakeBaseDirection, &gameGrid, snakeBaseGridPos, snakeBaseBodyLength);
GameState gameState;

int main()
{
    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60);

    gameGrid.LoadTex();
    snake.LoadTex();

    // Main game loop
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();

    return 0;
}

void Update()
{
    gameState = snake.gameState;

    if (gameState == GameState::Play)
    {
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            bufferDirection = Direction::Up;
        }
        else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            bufferDirection = Direction::Down;
        }
        else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            bufferDirection = Direction::Left;
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            bufferDirection = Direction::Right;
        }

        frameCounter++;
        if (frameCounter >= updateFrame)
        {
            frameCounter -= updateFrame;
            snake.ChangeDirection(bufferDirection);
            snake.Update();
        }
    }
    else
    {
        if (IsKeyDown(KEY_SPACE))
        {
            bool regenarateGame = gameState != GameState::NotStarted;
            snake.StartNewGame(snakeBaseGridPos, snakeBaseDirection, snakeBaseBodyLength, regenarateGame);
            bufferDirection = Direction::Up;
        }
    }

}

void Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    gameGrid.Draw();
    snake.Draw(screenWidth);

    switch (gameState)
    {
        case GameState::NotStarted :
            TextPlus::DrawTextCenter("Snake", floor(screenWidth / 3), 40, 25, WHITE);
            break;
        case GameState::Play :
            TextPlus::DrawTextCenter("Snake", floor(screenWidth / 3), 40, 25, WHITE);
            break;
        case GameState::Victory:
            TextPlus::DrawTextCenter("Victory", floor(screenWidth / 3), 40, 25, WHITE);
            break;
        case GameState::Defeat:
            TextPlus::DrawTextCenter("Defeat", floor(screenWidth / 3), 40, 25, WHITE);
            break;
    }

    if (gameState != GameState::Play)
    {
        TextPlus::DrawTextCenter("Press Space to play", floor(screenWidth / 2), 70, 25, WHITE);
    }

    EndDrawing();
}