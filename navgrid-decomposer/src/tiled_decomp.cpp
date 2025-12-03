#include "tiled_decomp.h"
#include "raylib.h"
#include <algorithm>

std::vector<Rect2D> TiledGreedyRectCover(const Grid2D& grid, int tile_size, uint8_t max_rect_size)
{
    const int grid_w = grid.Width();
    const int grid_h = grid.Height();

    tile_size = std::max(tile_size, 1);

    std::vector<Rect2D> out;

    for (int tile_y0 = 0; tile_y0 < grid_h; tile_y0 += tile_size)
    {
        for (int tile_x0 = 0; tile_x0 < grid_w; tile_x0 += tile_size)
        {
            const int tile_x1 = std::min(tile_x0 + tile_size, grid_w);
            const int tile_y1 = std::min(tile_y0 + tile_size, grid_h);

            const int local_w = tile_x1 - tile_x0;
            const int local_h = tile_y1 - tile_y0;

            Grid2D sub(local_w, local_h);
            sub.Clear(0);

            for (int y = 0; y < local_h; ++y)
                for (int x = 0; x < local_w; ++x)
                    sub.Set(x, y, grid.Get(tile_x0 + x, tile_y0 + y));

            std::vector<Rect2D> local_rects = GreedyRectCover(sub, max_rect_size);

            out.reserve(out.size() + local_rects.size());
            for (const Rect2D& r : local_rects)
            {
                out.emplace_back(
                    tile_x0 + r.GetX0(),
                    tile_x0 + r.GetX1(),
                    tile_y0 + r.GetY0(),
                    tile_y0 + r.GetY1()
                );
            }
        }
    }

    return out;
}

void DrawTileGrid(Vector2 origin, int grid_w, int grid_h, int tile_size, int cell_size, Color color)
{
    tile_size = std::max(tile_size, 1);

    for (int x = 0; x <= grid_w; x += tile_size)
    {
        DrawLine((int)origin.x + x * cell_size,
            (int)origin.y,
            (int)origin.x + x * cell_size,
            (int)origin.y + grid_h * cell_size,
            color);
    }

    for (int y = 0; y <= grid_h; y += tile_size)
    {
        DrawLine((int)origin.x,
            (int)origin.y + y * cell_size,
            (int)origin.x + grid_w * cell_size,
            (int)origin.y + y * cell_size,
            color);
    }
}
