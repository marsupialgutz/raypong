#include <raylib.h>

typedef enum GameScreen { TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;
    int scorePlayer1 = 0;
    int scorePlayer2 = 0;
    int framesCounter = 0;
    bool winner;
    Vector2 rectPos = {(float)30, (float)screenHeight / 2 - 50};
    Vector2 rect2Pos = {(float)screenWidth - 50, (float)screenHeight / 2 - 50};
    Vector2 ballPos = {(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 rectSize = {20, 100};
    Vector2 ballSpeed = {1.5f, 1.5f};
    GameScreen currentScreen = TITLE;
    InitWindow(screenWidth, screenHeight, "raypong");
    SetTargetFPS(144);

    while (!WindowShouldClose()) {

        switch (currentScreen) {

            case TITLE: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    currentScreen = GAMEPLAY;
            }
            break;
            
            case GAMEPLAY: {
                if (scorePlayer1 == 10) {
                    winner = false;
                    currentScreen = ENDING;
                }
                if (scorePlayer2 == 10) {
                    winner = true;
                    currentScreen = ENDING;
                }
            }
            break;
            
            case ENDING: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                    currentScreen = TITLE;
            }
            break;
            
            default:
            break;
        
        }

        if (IsKeyDown(KEY_W) && rectPos.y >= 30)
            rectPos.y -= 3.0f;
        
        if (IsKeyDown(KEY_S) && rectPos.y <= 320)
            rectPos.y += 3.0f;
        
        if (IsKeyDown(KEY_UP) && rect2Pos.y >= 30)
            rect2Pos.y -= 3.0f;
        
        if (IsKeyDown(KEY_DOWN) && rect2Pos.y <= 320)
            rect2Pos.y += 3.0f;
        
        BeginDrawing();

        switch (currentScreen) {

            case TITLE: {
                scorePlayer1 = 0;
                scorePlayer2 = 0;

                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawText("PONG", 20, 20, 40, WHITE);
                DrawText("PRESS ENTER or TAP to begin!", 240, 220, 20, WHITE);
            }
            break;

            case GAMEPLAY: {
                ClearBackground(BLACK);
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
                DrawLine(screenWidth / 2, 20, screenWidth / 2, 430, WHITE);
                DrawLine(20, 20, 780, 20, WHITE);
                DrawLine(20, 430, 780, 430, WHITE);
                DrawLine(20, 20, 20, 430, WHITE);
                DrawLine(780, 20, 780, 430, WHITE);
                DrawRectangleV(rectPos, rectSize, WHITE);
                DrawRectangleV(rect2Pos, rectSize, WHITE);
                DrawCircleV(ballPos, 20, WHITE);
                DrawText(TextFormat("Player 1 score: %d", scorePlayer1), screenWidth / 10, 30, 30, WHITE);
                DrawText(TextFormat("Player 2 score: %d", scorePlayer2), screenWidth / 1.75, 30, 30, WHITE);

                ballPos.x += ballSpeed.x;
                ballPos.y += ballSpeed.y;

                if (ballPos.y - (ballPos.y / 2) <= 20 || (ballPos.y + 20) >= 430)
                    ballSpeed.y *= -1;
                
                if (ballPos.x <= 60 && (ballPos.y >= rectPos.y && ballPos.y <= rectPos.y + 100))
                    ballSpeed.x *= -1;
                
                if (ballPos.x >= 740 && (ballPos.y >= rect2Pos.y && ballPos.y <= rect2Pos.y + 100))
                    ballSpeed.x *= -1;

                if (ballPos.x <= 0) {
                    ballPos.x = screenWidth / 2;
                    scorePlayer2++;
                }
                
                if (ballPos.x >= screenWidth) {
                    ballPos.x = screenWidth / 2;
                    scorePlayer1++;
                }
                
                DrawFPS(5, 0);
            }
            break;

            case ENDING: {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            
                if (winner)
                    DrawText("Player 2 wins!", 255, 120, 40, WHITE);
            
                else
                    DrawText("Player 1 wins!", 260, 120, 40, WHITE);

                DrawText("PRESS ENTER or TAP to return to the title screen!", 120, 220, 20, WHITE);
            }
            break;

            default:
            break;

        }

        EndDrawing();

    }

    CloseWindow();
    return 0;

}