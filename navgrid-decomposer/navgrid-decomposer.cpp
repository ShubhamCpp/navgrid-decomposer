// navgrid-decomposer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Visualization is based on raylib examples:
// https://www.raylib.com/examples.html

#include "raylib.h"
#include "grid.h"
#include "greedy_rect.h"
#include "tiled_decomp.h"

#define GRID_CELL_SIZE    24
#define MAX_GRID_CELLS_X  30
#define MAX_GRID_CELLS_Y  20

static void DrawGridLines(Vector2 origin, int w, int h)
{
    for (int y = 0; y <= h; y++)
    {
        DrawLine((int)origin.x,
            (int)origin.y + y * GRID_CELL_SIZE,
            (int)origin.x + w * GRID_CELL_SIZE,
            (int)origin.y + y * GRID_CELL_SIZE,
            GRAY);
    }

    for (int x = 0; x <= w; x++)
    {
        DrawLine((int)origin.x + x * GRID_CELL_SIZE,
            (int)origin.y,
            (int)origin.x + x * GRID_CELL_SIZE,
            (int)origin.y + h * GRID_CELL_SIZE,
            GRAY);
    }
}

static void DrawCells(const Grid2D& grid, Vector2 origin)
{
    for (int y = 0; y < grid.Height(); y++)
    {
        for (int x = 0; x < grid.Width(); x++)
        {
            if (grid.Get(x, y))
            {
                DrawRectangle((int)origin.x + x * GRID_CELL_SIZE,
                    (int)origin.y + y * GRID_CELL_SIZE,
                    GRID_CELL_SIZE, GRID_CELL_SIZE,
                    CLITERAL(Color){ 60, 140, 230, 200 });
            }
        }
    }
}

int main()
{
    const int pad = 40;

    // Window sized to fit the grid + a little HUD space
    const int screenWidth = pad * 2 + MAX_GRID_CELLS_X * GRID_CELL_SIZE;
    const int screenHeight = pad * 2 + MAX_GRID_CELLS_Y * GRID_CELL_SIZE + 70;

    InitWindow(screenWidth, screenHeight, "navgrid-decomposer (grid viewer)");
    SetTargetFPS(60);

    Vector2 gridPos = { (float)pad, (float)(pad + 50) };

    Grid2D grid(MAX_GRID_CELLS_X, MAX_GRID_CELLS_Y);

    // Tunable parameters

    int density = 86;     // percent filled
    uint32_t seed = 1337;
    bool showGridLines = true;

    grid.FillRandom(density, seed);

    // Greedy combination
    std::vector<Rect2D> rects;
    bool showRects = false;
    int max_size = 8;

    // Tiled sub-division + convex decomposition
    bool tiled_mode = false;
    int tile_size = 8;

    while (!WindowShouldClose())
    {
        // ---- Input ----
        if (IsKeyPressed(KEY_SPACE))
        {
            seed++;
            grid.FillRandom(density, seed);
        }

        if (IsKeyPressed(KEY_C))
        {
            grid.Clear(0);
        }

        if (IsKeyPressed(KEY_G))
        {
            showGridLines = !showGridLines;
        }

        if (IsKeyPressed(KEY_LEFT_BRACKET))
        {
            density -= 5;
            if (density < 0) density = 0;
            grid.FillRandom(density, seed);
        }

        if (IsKeyPressed(KEY_RIGHT_BRACKET))
        {
            density += 5;
            if (density > 100) density = 100;
            grid.FillRandom(density, seed);
        }

        // Click to toggle
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 m = GetMousePosition();
            int gx = (int)((m.x - gridPos.x) / GRID_CELL_SIZE);
            int gy = (int)((m.y - gridPos.y) / GRID_CELL_SIZE);

            if (grid.InBounds(gx, gy))
            {
                grid.Toggle(gx, gy);
            }
        }

        if (IsKeyPressed(KEY_T)) tiled_mode = !tiled_mode;

        if (IsKeyPressed(KEY_MINUS)) { tile_size = std::max(1, tile_size - 1); if (showRects) rects.clear(); }
        if (IsKeyPressed(KEY_EQUAL)) { tile_size = std::min(64, tile_size + 1); if (showRects) rects.clear(); }

        if (IsKeyPressed(KEY_ENTER))
        {
            showRects = !showRects;
            if (showRects)
            {
                rects = tiled_mode
                    ? TiledGreedyRectCover(grid, tile_size, max_size)
                    : GreedyRectCover(grid, max_size);
            }
            else rects.clear();
        }


        // ---- Draw ----
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("SPACE: randomize   [ ]: density   G: grid lines   C: clear   LMB: toggle cell   T: toggle algo   ENTER: greedy",
            pad, pad, 14, DARKGRAY);

        DrawText(TextFormat("seed=%u   density=%d%%", seed, density),
            pad, pad + 24, 18, GRAY);

        DrawCells(grid, gridPos);

        if (showGridLines)
            DrawGridLines(gridPos, grid.Width(), grid.Height());

        // Outer border
        DrawRectangleLines((int)gridPos.x, (int)gridPos.y,
            grid.Width() * GRID_CELL_SIZE,
            grid.Height() * GRID_CELL_SIZE,
            DARKGRAY);

        if (showRects)
        {
            // Greedy rectangles
            for (const Rect2D& r : rects) {
                DrawRectangleLines(
                    (int)gridPos.x + r.GetX0() * GRID_CELL_SIZE,
                    (int)gridPos.y + r.GetY0() * GRID_CELL_SIZE,
                    r.W() * GRID_CELL_SIZE,
                    r.H() * GRID_CELL_SIZE,
                    ORANGE
                );
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

