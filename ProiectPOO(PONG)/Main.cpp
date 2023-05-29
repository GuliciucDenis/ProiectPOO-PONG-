#include <iostream>
#include <raylib.h>

using namespace std;

Color Yellow = Color{ 243, 213, 91, 255 };

int Scor_jucator = 0;
int Scor_cpu = 0;

class Minge
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) 
        {
            Scor_cpu++;
            ResetBall();
        }

        if (x - radius <= 0)
        {
            Scor_jucator++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = { -1, 1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{

protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        LimitMovement();
    }
};

class CpuPaddle : public Paddle
{
public:
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }
        LimitMovement();
    }
};

Minge minge;
Paddle jucator;
CpuPaddle cpu;

int main()
{
    
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "PONG");
    SetTargetFPS(60);

    minge.radius = 20;
    minge.x = screen_width / 2;
    minge.y = screen_height / 2;
    minge.speed_x = 7;
    minge.speed_y = 7;

    jucator.width = 20;
    jucator.height = 120;
    jucator.x = screen_width - jucator.width - 10;
    jucator.y = screen_height / 2 - jucator.height / 2;
    jucator.speed = 6;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        
        minge.Update();
        jucator.Update();
        cpu.Update(minge.y);

        
        if (CheckCollisionCircleRec(Vector2{ minge.x, minge.y }, minge.radius, Rectangle{ jucator.x, jucator.y, jucator.width, jucator.height }))
        {
           minge.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ minge.x, minge.y }, minge.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
        {
            minge.speed_x *= -1;
        }

        
        ClearBackground(BLACK);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, BLACK);
        DrawCircle(screen_width / 2, screen_height / 2, 150, WHITE);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        minge.Draw();
        cpu.Draw();
        jucator.Draw();
        DrawText(TextFormat("%i", Scor_cpu), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", Scor_jucator), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}